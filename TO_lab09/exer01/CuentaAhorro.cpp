// CuentaAhorro.cpp
#include "CuentaAhorro.h"

void CuentaAhorro::calcularInteres() {
    double tasaInteres = 0.005; // Tasa de interés para Cuenta de Ahorro.
    double interes = saldo * tasaInteres;
    saldo += interes;
    std::cout << "Interés de ahorro aplicado: " << interes << std::endl;
}
