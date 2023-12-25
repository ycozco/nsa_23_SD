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

