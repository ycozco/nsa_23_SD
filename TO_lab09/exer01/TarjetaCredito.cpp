// TarjetaCredito.cpp
#include "TarjetaCredito.h"

void TarjetaCredito::calcularInteres() {
    double tasaInteres = 0.20; // Tasa de interés para Tarjeta de Crédito.
    double interes = saldo * tasaInteres;
    saldo += interes;
    std::cout << "Interés de tarjeta de crédito aplicado: " << interes << std::endl;
}
