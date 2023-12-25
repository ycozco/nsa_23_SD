#include "GestorCuentas.h"
#include "Usuario.h"
#include "CuentaAhorro.h"
#include <iostream>
#include <thread>
#include <mutex>

std::mutex printMutex;

void operacionUsuario(Usuario& usuario, Usuario& otroUsuario) {
    int opcion, subOpcion;
    double cantidad;
    size_t indiceCuenta = 0; // Asumiendo una sola cuenta por usuario

    do {
        {
            std::lock_guard<std::mutex> lock(printMutex);
            std::cout << "\n[Hilo " << std::this_thread::get_id() << "] " << usuario.getNombre() << " - Menú de Operaciones\n";
            std::cout << "1. Depositar\n";
            std::cout << "2. Retirar\n";
            std::cout << "3. Salir\n";
            std::cout << "Seleccione una opción: ";
        }
        std::cin >> opcion;

        if (opcion == 1 || opcion == 2) {
            std::lock_guard<std::mutex> lock(printMutex);
            std::cout << "1. En cuenta propia\n";
            std::cout << "2. En cuenta externa\n";
            std::cout << "Seleccione destino de la operación: ";
            std::cin >> subOpcion;

            std::cout << "Ingrese la cantidad: ";
            std::cin >> cantidad;

            if (opcion == 1) { // Depositar
                if (subOpcion == 1) usuario.operacionDeposito(cantidad, indiceCuenta);
                else usuario.operacionDepositoExterno(cantidad, otroUsuario.getCuenta(indiceCuenta));
            } else if (opcion == 2) { // Retirar
                if (subOpcion == 1) usuario.operacionRetiro(cantidad, indiceCuenta);
                else usuario.operacionRetiroExterno(cantidad, otroUsuario.getCuenta(indiceCuenta));
            }
        }
    } while (opcion != 3);

    {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout << "[Hilo " << std::this_thread::get_id() << "] " << usuario.getNombre() << " - Fin de operaciones\n";
    }
}

int main() {
    Usuario usuario1("Usuario1"), usuario2("Usuario2");
    std::shared_ptr<Cuenta> cuentaUsuario1 = std::make_shared<CuentaAhorro>(),
                           cuentaUsuario2 = std::make_shared<CuentaAhorro>();
    cuentaUsuario1->depositar(100);
    cuentaUsuario2->depositar(100);
    usuario1.agregarCuenta(cuentaUsuario1);
    usuario2.agregarCuenta(cuentaUsuario2);

    std::cout << "Cuentas creadas con saldo inicial de 100.\n";
    std::cout << "Usuario1 (Hilo: "<< std::this_thread::get_id() << "), Saldo: " << cuentaUsuario1->obtenerSaldo() << std::endl;
    std::cout << "Usuario2 (Hilo: "<< std::this_thread::get_id() << "), Saldo: " << cuentaUsuario2->obtenerSaldo() << std::endl;

    std::thread hiloUsuario1(operacionUsuario, std::ref(usuario1), std::ref(usuario2));
    std::thread hiloUsuario2(operacionUsuario, std::ref(usuario2), std::ref(usuario1));

    hiloUsuario1.join();
    hiloUsuario2.join();

    return 0;
}
