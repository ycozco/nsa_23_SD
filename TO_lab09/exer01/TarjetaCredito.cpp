// TarjetaCredito.cpp
#include "TarjetaCredito.h"
#include "Usuario.h"

#include "Cuenta.h"
void TarjetaCredito::calcularInteres(double tasaInteres){
    double interes = saldo * tasaInteres;
    saldo += interes;
    std::cout << "Interés de tarjeta de crédito aplicado: " << interes << std::endl;
}
TarjetaCredito::TarjetaCredito() : Cuenta("Tarjeta de Crédito") {
    std::cout << "Tarjeta de Crédito creada." << std::endl;
}