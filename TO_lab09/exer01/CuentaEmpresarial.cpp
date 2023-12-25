// CuentaEmpresarial.cpp
#include "CuentaEmpresarial.h"

void CuentaEmpresarial::calcularInteres() {
    double tasaInteres = 0.02; // Tasa de interés para Cuenta Empresarial.
    double interes = saldo * tasaInteres;
    saldo += interes;
    std::cout << "Interés de cuenta empresarial aplicado: " << interes << std::endl;
}
