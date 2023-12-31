// CuentaPluss.cpp
#include "CuentaPluss.h"
#include "Usuario.h"
void CuentaPluss::calcularInteres(double tasaInteres) {
    double interes = saldo * tasaInteres;
    saldo += interes;
    std::cout << "Interés de Cuenta Pluss aplicado: " << interes << std::endl;
}

CuentaPluss::CuentaPluss() : Cuenta("Plus") {
    std::cout << "Cuenta Plus creada." << std::endl;
}