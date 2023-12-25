// Usuario.h
#ifndef USUARIO_H
#define USUARIO_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "Cuenta.h"

class Usuario {
private:
    std::string nombre;
    std::vector<std::shared_ptr<Cuenta>> cuentas;

public:
    Usuario(const std::string& nombre) : nombre(nombre) {}

    void agregarCuenta(const std::shared_ptr<Cuenta>& cuenta);
    void operacionDeposito(double cantidad, size_t indiceCuenta);
    void operacionDepositoExterno(double cantidad, const std::shared_ptr<Cuenta>& cuentaExterna);
    void operacionRetiroExterno(double cantidad, const std::shared_ptr<Cuenta>& cuentaExterna);
    void operacionRetiro(double cantidad, size_t indiceCuenta);
    const std::string& getNombre() const {
        return nombre;
    }
};

#endif // USUARIO_H
