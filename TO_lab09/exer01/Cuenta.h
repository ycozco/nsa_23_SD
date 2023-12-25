// Cuenta.h
#include <memory>
#ifndef CUENTA_H
#define CUENTA_H

#include <iostream>
#include <string>

class Cuenta {
protected:
    double saldo;

public:
    Cuenta() : saldo(0) {}
    virtual ~Cuenta() {}

    virtual void calcularInteres() = 0;
    virtual void depositar(double cantidad);
    virtual void retirar(double cantidad);
    virtual double obtenerSaldo() const;
    // ... (otros métodos como transferencias, préstamos, etc.)
};

#endif // CUENTA_H
