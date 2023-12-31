// Usuario.cpp
#include "Usuario.h"

void Usuario::agregarCuenta(const std::shared_ptr<Cuenta>& cuenta) {
    cuentas.push_back(cuenta);
}

void Usuario::operacionDeposito(double cantidad, size_t indiceCuenta) {
    if (indiceCuenta < cuentas.size()) {
        cuentas[indiceCuenta]->depositar(cantidad);
    } else {
        std::cerr << "Índice de cuenta inválido para " << nombre << std::endl;
    }
}

void Usuario::operacionRetiro(double cantidad, size_t indiceCuenta) {
    if (indiceCuenta < cuentas.size()) {
        cuentas[indiceCuenta]->retirar(cantidad);
    } else {
        std::cerr << "Índice de cuenta inválido para " << nombre << std::endl;
    }
}

void Usuario::operacionDepositoExterno(double cantidad, const std::shared_ptr<Cuenta>& cuentaExterna) {
    if (cuentaExterna) {
        cuentaExterna->depositar(cantidad);
    } else {
        std::cerr << "Cuenta externa no válida para " << nombre << std::endl;
    }
}

void Usuario::operacionRetiroExterno(double cantidad, const std::shared_ptr<Cuenta>& cuentaExterna) {
    std::cerr << "Operación de retiro no autorizada en cuenta externa por " << nombre << std::endl;
}

void Usuario::generarEstadoCuenta(const std::string& tipoCuenta, const std::string& fechaCorte) {
    std::cout << "Estado de Cuenta para " << nombre << " - Tipo: " << tipoCuenta << " - Fecha de Corte: " << fechaCorte << std::endl;
    for (const auto& cuenta : cuentas) {
        if (cuenta->obtenerTipo() == tipoCuenta) {
            std::cout << "Saldo actual: " << cuenta->obtenerSaldo() << std::endl;
            // Aquí asumimos que cada cuenta tiene un método para obtener transacciones
            auto transacciones = cuenta->obtenerTransaccionesHasta(fechaCorte);
            for (const auto& transaccion : transacciones) {
                std::cout << "Transacción: " << transaccion.tipo << " - Fecha: " << transaccion.fecha << std::endl;
            }
        }
    }
}
void Usuario::generarEstadoCuenta(const std::string& fechaCorte) {
    for (const auto& cuenta : cuentas) {
        std::cout << "Estado de cuenta para la cuenta: " << std::endl;
        auto transacciones = cuenta->obtenerTransaccionesHasta(fechaCorte);
        for (const auto& transaccion : transacciones) {
            std::cout << "Fecha: " << transaccion.fecha << ", Tipo: " << transaccion.tipo << ", Cantidad: " << transaccion.cantidad << std::endl;
        }
    }
}

void Usuario::finalizar() {

    std::cout << "Finalizando sesión de " << nombre << std::endl;
}