#include "GestorCuentas.h"
#include "Usuario.h"
#include "CuentaAhorro.h"
#include "CuentaEmpresarial.h"
#include "CuentaPluss.h"
#include <iostream>
#include <thread>

int main() {
    std::cout << "Iniciando el sistema de gestión de cuentas..." << std::endl;

    // Crear una instancia de GestorCuentas (Singleton).
    GestorCuentas* gestor = GestorCuentas::obtenerInstancia();

    // Crear usuarios y asignarles cuentas.
    Usuario usuario1("Usuario1");
    Usuario usuario2("Usuario2");

    std::cout << "Creando cuentas y asignándolas a los usuarios..." << std::endl;
    std::shared_ptr<Cuenta> cuentaUsuario1 = std::make_shared<CuentaAhorro>();
    std::shared_ptr<Cuenta> cuentaUsuario2 = std::make_shared<CuentaAhorro>();

    usuario1.agregarCuenta(cuentaUsuario1);
    usuario2.agregarCuenta(cuentaUsuario2);

    // Función lambda para imprimir desde los hilos
    auto operacionConInfo = [](Usuario& usuario, double cantidad, size_t indiceCuenta) {
        std::cout << "Hilo " << std::this_thread::get_id() << " (" << usuario.getNombre() << ") realizando operación de depósito en su cuenta." << std::endl;
        usuario.operacionDeposito(cantidad, indiceCuenta);
    };

    std::cout << "Iniciando operaciones concurrentes de depósito..." << std::endl;
    std::thread hiloUsuario1(operacionConInfo, std::ref(usuario1), 100.0, 0);
    std::thread hiloUsuario2(operacionConInfo, std::ref(usuario2), 200.0, 0);

    // Unir hilos.
    hiloUsuario1.join();
    hiloUsuario2.join();

    std::cout << "Operaciones concurrentes completadas." << std::endl;

    // Intentar realizar una operación no autorizada.
    std::cout << "Usuario2 intentando operación no autorizada de depósito en la cuenta de Usuario1:" << std::endl;
    usuario2.operacionDepositoExterno(50.0, cuentaUsuario1);  // Usuario2 intenta depositar en la cuenta de Usuario1

    std::cout << "Usuario2 intentando operación no autorizada de retiro en la cuenta de Usuario1:" << std::endl;
    usuario2.operacionRetiroExterno(50.0, cuentaUsuario1);  // Usuario2 intenta retirar de la cuenta de Usuario1

    std::cout << "Programa finalizado." << std::endl;

    return 0;
}
