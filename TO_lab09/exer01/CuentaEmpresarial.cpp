// CuentaEmpresarial.cpp
#include "CuentaEmpresarial.h"
#include "Usuario.h"
#include "Cuenta.h"
void CuentaEmpresarial::calcularInteres(double tasaInteres){
  
    double interes = saldo * tasaInteres;
    saldo += interes;
    std::cout << "Interés de cuenta empresarial aplicado: " << interes << std::endl;
}

CuentaEmpresarial:: CuentaEmpresarial() : Cuenta("Empresarial") {
    std::cout << "Cuenta Empresarial creada." << std::endl;
}