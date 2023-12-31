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
    void operacionRetiro(double cantidad, size_t indiceCuenta);
    void operacionDepositoExterno(double cantidad, const std::shared_ptr<Cuenta>& cuentaExterna);
    void operacionRetiroExterno(double cantidad, const std::shared_ptr<Cuenta>& cuentaExterna);
    void generarEstadoCuenta(const std::string& tipoCuenta, const std::string& fechaCorte);
    const std::string& getNombre() const {
        return nombre;
    }
    void generarEstadoCuenta(const std::string& fechaCorte);
    std::shared_ptr<Cuenta> getCuenta(size_t indice) const {
        return indice < cuentas.size() ? cuentas[indice] : nullptr;
    }
    void finalizar();
};

#endif // USUARIO_H
