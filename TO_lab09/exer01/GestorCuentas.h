// GestorCuentas.h
#ifndef GESTORCUENTAS_H
#define GESTORCUENTAS_H

#include <memory>
#include <vector>
#include <mutex>
#include "Cuenta.h"

class GestorCuentas {
private:
    static std::unique_ptr<GestorCuentas> instancia;
    std::vector<std::shared_ptr<Cuenta>> cuentas;
    static std::mutex mutexInstancia;

    // Constructor privado para prevenir instanciación externa.
    GestorCuentas() {}

public:
    // Eliminamos la posibilidad de copia o asignación.
    GestorCuentas(const GestorCuentas&) = delete;
    GestorCuentas& operator=(const GestorCuentas&) = delete;

    static GestorCuentas* obtenerInstancia();

    // Método para agregar una cuenta al gestor.
    void agregarCuenta(const std::shared_ptr<Cuenta>& cuenta);

    // ... otros métodos como transferencias, préstamos, etc.
};

#endif // GESTORCUENTAS_H
