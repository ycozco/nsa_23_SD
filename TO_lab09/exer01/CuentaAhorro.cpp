// CuentaAhorro.cpp
#include "CuentaAhorro.h"
#include "Usuario.h"
void CuentaAhorro::calcularInteres(double tasaInteres){
    double interes = saldo  * tasaInteres; // Tasa de interés para Cuenta de Ahorro.
    saldo += interes;
    std::cout << "Interés de ahorro aplicado: " << interes << std::endl;
}
CuentaAhorro::CuentaAhorro() : Cuenta("Ahorro") {
    std::cout << "Cuenta de Ahorro creada." << std::endl;
}