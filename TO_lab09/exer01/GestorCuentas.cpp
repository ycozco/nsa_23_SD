// GestorCuentas.cpp
#include "GestorCuentas.h"
#include "Usuario.h"
std::unique_ptr<GestorCuentas> GestorCuentas::instancia = nullptr;
std::mutex GestorCuentas::mutexInstancia;

GestorCuentas* GestorCuentas::obtenerInstancia() {
    std::lock_guard<std::mutex> lock(mutexInstancia);
    if (!instancia) {
        instancia = std::unique_ptr<GestorCuentas>(new GestorCuentas());
    }
    return instancia.get();
}

void GestorCuentas::agregarCuenta(const std::shared_ptr<Cuenta>& cuenta) {
    std::lock_guard<std::mutex> lock(mutexInstancia);
    cuentas.push_back(cuenta);
    std::cout << "Cuenta agregada al gestor." << std::endl;
}

// Implementación de otros métodos...
