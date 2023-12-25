#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>
#include <vector>
#include <memory>

// Suponiendo que estas clases están definidas en archivos respectivos
#include "Usuario.h"
#include "CuentaAhorro.h"

std::mutex mu;
std::condition_variable cv;
int opcionGlobal = 0;
bool finalizar = false;
std::map<std::string, std::pair<std::thread::id, Usuario*>> usuarios;
std::string usuarioSeleccionadoGlobal;

void operacionUsuario(Usuario& usuario) {
    while (true) {
        std::unique_lock<std::mutex> lock(mu);
        cv.wait(lock, [&usuario] { return usuario.getNombre() == usuarioSeleccionadoGlobal || finalizar; });

        if (finalizar) {
            std::cout << "[Hilo " << std::this_thread::get_id() << "] " << usuario.getNombre() << " finalizando." << std::endl;
            break;
        }

        if (opcionGlobal == 1) {
            // Implementación de lógica para depositar
        } else if (opcionGlobal == 2) {
            // Implementación de lógica para retirar
        }

        usuarioSeleccionadoGlobal = "";
        opcionGlobal = 0;
        lock.unlock();
        cv.notify_all();
    }
}

void interfazPrincipal() {
    int indiceUsuario;
    double cantidad;

    std::cout << "[Hilo Principal] Iniciando menú principal." << std::endl;
    std::cout << "Usuarios iniciales y sus saldos:" << std::endl;
    for (const auto& [nombre, info] : usuarios) {
        std::cout << nombre << " (Hilo: " << info.first << "), Saldo: " << info.second->getCuenta(0)->obtenerSaldo() << std::endl;
    }

    while (true) {
        std::unique_lock<std::mutex> lock(mu);
        std::cout << "\n[Hilo Principal] Menú Principal\n";
        std::cout << "1. Depositar\n";
        std::cout << "2. Retirar\n";
        std::cout << "3. Salir\n";
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

            std::cout << "Ingrese la cantidad: ";
            std::cin >> cantidad;

            // Lógica adicional para manejar depósitos/retiros
        }

        if (opcionGlobal == 3) {
            finalizar = true;
            cv.notify_all();
            break;
        }

        lock.unlock();
        cv.notify_all();
        cv.wait(lock, [] { return usuarioSeleccionadoGlobal.empty(); });
    }
}

int main() {
    // Creación de usuarios y asignación de cuentas
    Usuario usuario1("Usuario1"), usuario2("Usuario2");
    std::shared_ptr<Cuenta> cuentaUsuario1 = std::make_shared<CuentaAhorro>(),
                           cuentaUsuario2 = std::make_shared<CuentaAhorro>();
    cuentaUsuario1->depositar(100);
    cuentaUsuario2->depositar(100);
    usuario1.agregarCuenta(cuentaUsuario1);
    usuario2.agregarCuenta(cuentaUsuario2);

    std::thread hiloUsuario1(operacionUsuario, std::ref(usuario1));
    std::thread hiloUsuario2(operacionUsuario, std::ref(usuario2));

    usuarios["Usuario1"] = {hiloUsuario1.get_id(), &usuario1};
    usuarios["Usuario2"] = {hiloUsuario2.get_id(), &usuario2};

    std::thread hiloInterfaz(interfazPrincipal);

    hiloInterfaz.join();
    hiloUsuario1.join();
    hiloUsuario2.join();

    std::cout << "[Hilo Principal] Programa finalizado." << std::endl;
    return 0;
}
