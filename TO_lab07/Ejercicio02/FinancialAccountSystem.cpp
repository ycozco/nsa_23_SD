#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <functional>

std::mutex cuentaMutex;

class Cuenta {
protected:
    double saldo;

public:
    Cuenta() : saldo(0) {}

    virtual void calcularInteres() = 0;

    virtual void depositar(double cantidad) {
        if (cantidad > 0) {
            saldo += cantidad;
            std::cout << "Depositado: " << cantidad << ". Nuevo saldo: " << saldo << std::endl;
        } else {
            std::cout << "Cantidad a depositar no puede ser negativa." << std::endl;
        }
    }

    virtual void depositar(double cantidad, const std::string& descripcion) {
        depositar(cantidad);
        std::cout << "Descripción de la transacción: " << descripcion << std::endl;
    }

    virtual void retirar(double cantidad) {
        if (cantidad <= saldo) {
            saldo -= cantidad;
            std::cout << "Retirado: " << cantidad << ". Nuevo saldo: " << saldo << std::endl;
        } else {
            std::cout << "Fondos insuficientes para retirar: " << cantidad << std::endl;
        }
    }
    // Versión original que acepta solo la cantidad
    virtual void depositarSeguro(double cantidad) {
        std::lock_guard<std::mutex> lock(cuentaMutex);
        std::cout << "Hilo " << std::this_thread::get_id() << " accediendo a la cuenta." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        depositar(cantidad);
    }

    // Versión sobrecargada que acepta cantidad y descripción
    virtual void depositarSeguro(double cantidad, const std::string& descripcion) {
        std::lock_guard<std::mutex> lock(cuentaMutex);
        std::cout << "Hilo " << std::this_thread::get_id() << " accediendo a la cuenta con descripción." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        depositar(cantidad);
        std::cout << "Descripción de la transacción: " << descripcion << std::endl;
    }

    virtual double obtenerSaldo() const {
        return saldo;
    }

    virtual ~Cuenta() {}
};

class CuentaAhorro : public Cuenta {
public:
    void calcularInteres() override {
        double interes = saldo * 0.0045;
        saldo += interes;
        std::cout << "Interés de ahorro aplicado: " << interes << std::endl;
    }
};

class CuentaJoven : public Cuenta {
public:
    void calcularInteres() override {
        double interes = saldo * 0.0055;
        saldo += interes;
        std::cout << "Interés de cuenta joven aplicado: " << interes << std::endl;
    }
};

class CuentaPluss : public Cuenta {
public:
    void calcularInteres() override {
        // Implementación para Cuenta Pluss
    }
};

class CuentaEmpresarial : public Cuenta {
public:
    void calcularInteres() override {
        // Implementación para Cuenta Empresarial
    }
};

class TarjetaCredito : public Cuenta {
public:
    void calcularInteres() override {
        double interes = saldo * 0.15;
        saldo += interes;
        std::cout << "Interés de tarjeta de crédito aplicado: " << interes << std::endl;
    }
};

class Cliente {
public:
    std::vector<std::shared_ptr<Cuenta>> cuentas;

    void agregarCuenta(std::shared_ptr<Cuenta> cuenta) {
        cuentas.push_back(cuenta);
        std::cout << "Nueva cuenta agregada al cliente." << std::endl;
    }

    void mostrarSaldos() {
        for (const auto& cuenta : cuentas) {
            std::cout << "Saldo de la cuenta: " << cuenta->obtenerSaldo() << std::endl;
        }
    }
};

class BuilderCuenta {
public:
    virtual std::shared_ptr<Cuenta> getCuentaAhorro() const {
        return std::make_shared<CuentaAhorro>();
    }

    virtual std::shared_ptr<Cuenta> getCuentaJoven() const {
        return std::make_shared<CuentaJoven>();
    }

    virtual std::shared_ptr<Cuenta> getTarjetaCredito() const {
        return std::make_shared<TarjetaCredito>();
    }
};

class Director {
    std::shared_ptr<BuilderCuenta> builder;

public:
    void setBuilder(const std::shared_ptr<BuilderCuenta>& newBuilder) {
        builder = newBuilder;
    }

    std::shared_ptr<Cuenta> construirCuentaAhorro() {
        return builder->getCuentaAhorro();
    }

    std::shared_ptr<Cuenta> construirCuentaJoven() {
        return builder->getCuentaJoven();
    }

    std::shared_ptr<Cuenta> construirTarjetaCredito() {
        return builder->getTarjetaCredito();
    }
};

template <typename Func>
void aplicarAjusteACuentas(Cliente& cliente, Func f) {
    for (auto& cuenta : cliente.cuentas) {
        f(cuenta);
    }
}

int main() {
    Director director;
    director.setBuilder(std::make_shared<BuilderCuenta>());

    Cliente cliente;
    auto cuentaCompartida = director.construirCuentaAhorro();
    cliente.agregarCuenta(cuentaCompartida);

    std::thread hilo1([&cuentaCompartida]() {
        cuentaCompartida->depositarSeguro(1000);
        cuentaCompartida->depositarSeguro(200, "Depósito de bonificación");
    });

    std::thread hilo2([&cuentaCompartida]() {
        cuentaCompartida->retirar(500);
    });

    hilo1.join();
    hilo2.join();

    auto ajustarInteres = [](std::shared_ptr<Cuenta>& cuenta) {
        // Aquí podrías ajustar los intereses o realizar otra operación
    };

    aplicarAjusteACuentas(cliente, ajustarInteres);

    cliente.mostrarSaldos();

    return 0;
}

// exec: g++ -std=c++11 -o FinancialAccountSystem FinancialAccountSystem.cpp -pthread && ./FinancialAccountSystem
