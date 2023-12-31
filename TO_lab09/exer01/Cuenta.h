// Cuenta.h
#include <memory>
#ifndef CUENTA_H
#define CUENTA_H

#include <vector>
#include <iostream>
#include <string>

struct Transaccion {
    std::string tipo; // "Depósito" o "Retiro"
    double cantidad;
    std::string fecha; // Formato "YYYY-MM-DD"
};

class Cuenta {
protected:
    double saldo;
    std::string tipo; // Declaración de la variable tipo en la clase base

public:
    std::vector<Transaccion> historialTransacciones;
    std::vector<Transaccion> obtenerTransaccionesHasta(const std::string& fechaCorte);
    Cuenta() : saldo(0), tipo("Desconocido") {} // Constructor base, el tipo se establece en "Desconocido"
    Cuenta(const std::string& tipoCuenta) : saldo(0), tipo(tipoCuenta) {} // Constructor que acepta el tipo de cuenta
    virtual ~Cuenta() {}

    virtual void calcularInteres(double tasaInteres)= 0;
    virtual void depositar(double cantidad);
    virtual void retirar(double cantidad);
    virtual double obtenerSaldo() const;
    const std::string& obtenerTipo() const { return tipo; } // Método para obtener el tipo de cuenta
    // ... (otros métodos como transferencias, préstamos, etc.)
};

#endif // CUENTA_H
