// CuentaPluss.cpp
#include "CuentaPluss.h"

void CuentaPluss::calcularInteres() {
    double tasaInteres = 0.01; // Tasa de interés para Cuenta Pluss.
    double interes = saldo * tasaInteres;
    saldo += interes;
    std::cout << "Interés de Cuenta Pluss aplicado: " << interes << std::endl;
}
