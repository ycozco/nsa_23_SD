#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>
#include <vector>
#include <memory>

#include "Usuario.h"
#include "CuentaAhorro.h"
#include "CuentaEmpresarial.h"
#include "CuentaPluss.h"
#include "Cuenta.h"
#include "TarjetaCredito.h"
#include "GestorCuentas.h"
std::mutex mu;
std::condition_variable cv;
int opcionGlobal = 0;
bool finalizar = false;
std::map<std::string, std::pair<std::thread, Usuario*>> usuarios;
std::string usuarioSeleccionadoGlobal;

void operacionUsuario(Usuario& usuario) {
    while (true) {
        std::unique_lock<std::mutex> lock(mu);
        cv.wait(lock, [&usuario] { return usuario.getNombre() == usuarioSeleccionadoGlobal || finalizar; });

        if (finalizar) {
            std::cout << "[Hilo " << std::this_thread::get_id() << "] " << usuario.getNombre() << " finalizando." << std::endl;
            break;
        }

        try {
            if (opcionGlobal == 1) {
                double cantidad;
                std::cout << "[Hilo " << std::this_thread::get_id() << "] " << usuario.getNombre() << " depositando." << std::endl;
                std::cout << "Ingrese la cantidad a depositar: ";
                std::cin >> cantidad;
                usuario.getCuenta(0)->depositar(cantidad);
                std::cout << "Depósito exitoso. Nuevo saldo: " << usuario.getCuenta(0)->obtenerSaldo() << std::endl;
            } else if (opcionGlobal == 2) {
                double cantidad;
                std::cout << "[Hilo " << std::this_thread::get_id() << "] " << usuario.getNombre() << " retirando." << std::endl;
                std::cout << "Ingrese la cantidad a retirar: ";
                std::cin >> cantidad;

                // Validar si el usuario tiene fondos suficientes antes de retirar
                if (cantidad > usuario.getCuenta(0)->obtenerSaldo()) {
                    throw std::runtime_error("Error: Fondos insuficientes.");
                }

                usuario.getCuenta(0)->retirar(cantidad);
                std::cout << "Retiro exitoso. Nuevo saldo: " << usuario.getCuenta(0)->obtenerSaldo() << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        usuarioSeleccionadoGlobal = "";
        opcionGlobal = 0;

        // Vuelve al menú principal
        lock.unlock();
        cv.notify_all();
    }
}

void interfazPrincipal() {
    int indiceUsuario;

    std::cout << "[Hilo Principal] Iniciando menú principal." << std::endl;

    while (true) {
        std::unique_lock<std::mutex> lock(mu);
        std::cout << "\n[Hilo Principal] Menú Principal\n";
        std::cout << "1. Depositar\n";
        std::cout << "2. Retirar\n";
        std::cout << "3. Salir\n";
        std::cout << "4. Crear Nuevo Usuario\n";
        std::cout << "[Hilo Principal] Seleccione una opción: ";
        std::cin >> opcionGlobal;

        if (opcionGlobal == 1 || opcionGlobal == 2) {
            std::cout << "Seleccione un usuario:\n";
            indiceUsuario = 1;
            for (const auto& [nombre, _] : usuarios) {
                std::cout << indiceUsuario++ << ". " << nombre << std::endl;
            }
            std::cin >> indiceUsuario;

            auto iter = std::next(usuarios.begin(), indiceUsuario - 1);
            usuarioSeleccionadoGlobal = iter->first;

            // Se notifica a los hilos de operación que deben ejecutar la operación para el usuario seleccionado
            cv.notify_all();
        }

        if (opcionGlobal == 3) {
            finalizar = true;
            cv.notify_all();
            break;
        }

        // Vuelve al menú principal
        cv.wait(lock, [] { return usuarioSeleccionadoGlobal.empty(); });
    }
}

int main() {
    // Creación de usuarios y asignación de cuentas
    Usuario usuario1("Usuario1"), usuario2("Usuario2");
    std::shared_ptr<CuentaAhorro> cuentaUsuario1 = std::make_shared<CuentaAhorro>(),
                                   cuentaUsuario2 = std::make_shared<CuentaAhorro>();
    cuentaUsuario1->depositar(100);
    cuentaUsuario2->depositar(100);
    usuario1.agregarCuenta(cuentaUsuario1);
    usuario2.agregarCuenta(cuentaUsuario2);

    std::thread hiloUsuario1(operacionUsuario, std::ref(usuario1));
    std::thread hiloUsuario2(operacionUsuario, std::ref(usuario2));

    usuarios["Usuario1"] = {std::move(hiloUsuario1), &usuario1};
    usuarios["Usuario2"] = {std::move(hiloUsuario2), &usuario2};

    std::thread hiloInterfaz(interfazPrincipal);

    hiloInterfaz.join();

    // Unir y limpiar todos los hilos y recursos al finalizar
    for (auto& [nombre, par] : usuarios) {
        par.second->finalizar(); // Asegúrate de tener un método para finalizar correctamente cada usuario
        if (par.first.joinable()) {
            par.first.join();
        }
        delete par.second; // Libera la memoria del usuario
    }

    std::cout << "[Hilo Principal] Programa finalizado." << std::endl;
    return 0;
}
