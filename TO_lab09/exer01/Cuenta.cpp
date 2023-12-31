// cuenta.cpp
#include "Cuenta.h"
#include "Usuario.h"
#include <iostream>
#include <ctime>
void Cuenta::depositar(double cantidad) {
    if (cantidad <= 0) {
        std::cerr << "La cantidad a depositar debe ser positiva." << std::endl;
        return;
    }
    saldo += cantidad;
    std::cout << "Depositado: " << cantidad << ". Saldo actual: " << saldo << std::endl;
    Transaccion transaccion{"Depósito", cantidad, obtenerFechaActual()};
    historialTransacciones.push_back(transaccion);
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
std::string obtenerFechaActual() {
    // Obtener el tiempo actual
    time_t tiempoActual = time(nullptr);

    // Convertir el tiempo a una estructura tm
    tm *estructuraTiempo = localtime(&tiempoActual);

    // Obtener el año, mes y día actual
    int anio = estructuraTiempo->tm_year + 1900;
    int mes = estructuraTiempo->tm_mon + 1;
    int dia = estructuraTiempo->tm_mday;

    // Crear una cadena de fecha en el formato deseado (YYYY-MM-DD)
    std::string fechaActual = std::to_string(anio) + "-" +
                              (mes < 10 ? "0" : "") + std::to_string(mes) + "-" +
                              (dia < 10 ? "0" : "") + std::to_string(dia);

    return fechaActual;
}

std::vector<Transaccion> Cuenta::obtenerTransaccionesHasta(const std::string& fechaCorte) {
    std::vector<Transaccion> transaccionesFiltradas;
    for (const auto& transaccion : historialTransacciones) {
        if (transaccion.fecha <= fechaCorte) {
            transaccionesFiltradas.push_back(transaccion);
        }
    }
    return transaccionesFiltradas;
}
 
// obtenerTipo()
std::string Cuenta::obtenerTipo() const {
    return tipo;
}