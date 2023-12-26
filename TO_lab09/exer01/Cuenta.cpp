// cuenta.cpp
#include "Cuenta.h"
#include <iostream>

void Cuenta::depositar(double cantidad) {
    if (cantidad <= 0) {
        std::cerr << "La cantidad a depositar debe ser positiva." << std::endl;
        return;
    }
    saldo += cantidad;
    std::cout << "Depositado: " << cantidad << ". Saldo actual: " << saldo << std::endl;
}

void Cuenta::retirar(double cantidad) {
    if (cantidad > saldo) {
        std::cerr << "Fondos insuficientes para retirar." << std::endl;
        return;
    }
    saldo -= cantidad;
    std::cout << "Retirado: " << cantidad << ". Saldo actual: " << saldo << std::endl;
}
double Cuenta::obtenerSaldo() const {
    return saldo;
}
// Aquí puedes agregar la implementación del método calcularInteres si es común a todas las cuentas,
// o bien dejarlo como un método virtual puro si cada subclase tiene su propia implementación.
