// Importaciones de bibliotecas estándar
#include <iostream>  // Para operaciones de entrada/salida
#include <vector>    // Para usar el contenedor std::vector
#include <string>    // Para usar objetos de tipo std::string
#include <memory>    // Para utilizar punteros inteligentes
#include <thread>    // Para manejo de hilos
#include <mutex>     // Para sincronización de hilos
#include <functional> // Para usar funciones como argumentos

// Definición de un mutex global para sincronizar el acceso a la cuenta
std::mutex cuentaMutex;

// Clase base para cuentas
class Cuenta {
protected:
    double saldo;  // Saldo de la cuenta

public:
    // Constructor
    Cuenta() : saldo(0) {}

    // Método virtual 
    virtual void calcularInteres() = 0;


    virtual void depositar(double cantidad) {
        if (cantidad > 0) {
            saldo += cantidad;
            std::cout << "Depositado: " << cantidad << ". Nuevo saldo: " << saldo << std::endl;
        } else {
            std::cout << "Cantidad a depositar no puede ser negativa." << std::endl;
        }
    }

    // Sobrecarga del método depositar 
    virtual void depositar(double cantidad, const std::string& descripcion) {
        depositar(cantidad);
        std::cout << "Descripción de la transacción: " << descripcion << std::endl;
    }

    // Método para retirar 
    virtual void retirar(double cantidad) {
        if (cantidad <= saldo) {
            saldo -= cantidad;
            std::cout << "Retirado: " << cantidad << ". Nuevo saldo: " << saldo << std::endl;
        } else {
            std::cout << "Fondos insuficientes para retirar: " << cantidad << std::endl;
        }
    }

    // Método para depositar de forma segura utilizando un mutex 
    virtual void depositarSeguro(double cantidad) {
        std::lock_guard<std::mutex> lock(cuentaMutex);
        std::cout << "Hilo " << std::this_thread::get_id() << " accediendo a la cuenta." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        depositar(cantidad);
    }

    // Sobrecarga del método depositarSeguro con descripción
    virtual void depositarSeguro(double cantidad, const std::string& descripcion) {
        std::lock_guard<std::mutex> lock(cuentaMutex);
        std::cout << "Hilo " << std::this_thread::get_id() << " accediendo a la cuenta con descripción." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        depositar(cantidad);
        std::cout << "Descripción de la transacción: " << descripcion << std::endl;
    }

    // Método para obtener el saldo actual de la cuenta
    virtual double obtenerSaldo() const {
        return saldo;
    }

    // Destructor virtual para permitir la destrucción apropiada de objetos de subclases
    virtual ~Cuenta() {}
};

// Subclases de Cuenta, implementando el método calcularInteres específico para cada tipo
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

// Clases adicionales como CuentaPluss y CuentaEmpresarial, cada una con su propia implementación del cálculo de interés
// ...

class TarjetaCredito : public Cuenta {
public:
    void calcularInteres() override {
        double interes = saldo * 0.15;
        saldo += interes;
        std::cout << "Interés de tarjeta de crédito aplicado: " << interes << std::endl;
    }
};

// Clase para representar a un cliente que posee múltiples cuentas
class Cliente {
public:
    std::vector<std::shared_ptr<Cuenta>> cuentas;  // Vector de cuentas del cliente

    // Método para agregar una cuenta al cliente
    void agregarCuenta(std::shared_ptr<Cuenta> cuenta) {
        cuentas.push_back(cuenta);
        std::cout << "Nueva cuenta agregada al cliente." << std::endl;
    }

    // Método para mostrar los saldos de todas las cuentas del cliente
    void mostrarSaldos() {
        for (const auto& cuenta : cuentas) {
            std::cout << "Saldo de la cuenta: " << cuenta->obtenerSaldo() << std::endl;
        }
    }
};

// Clase Builder para crear diferentes tipos de cuentas
class BuilderCuenta {
public:
    // Métodos para obtener diferentes tipos de cuentas
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

// Clase Director para orquestar la construcción de cuentas usando un Builder
class Director {
    std::shared_ptr<BuilderCuenta> builder;

public:
    // Método para establecer el constructor de cuentas
    void setBuilder(const std::shared_ptr<BuilderCuenta>& newBuilder) {
        builder = newBuilder;
    }

    // Métodos para construir diferentes tipos de cuentas
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

// Función plantilla para aplicar un ajuste a todas las cuentas de un cliente
template <typename Func>
void aplicarAjusteACuentas(Cliente& cliente, Func f) {
    for (auto& cuenta : cliente.cuentas) {
        f(cuenta);
    }
}
int main() {
    // Instanciar el director que gestionará la construcción de cuentas
    Director director;
    // Establecer el constructor de cuentas para el director
    director.setBuilder(std::make_shared<BuilderCuenta>());

    // Crear un objeto cliente
    Cliente cliente;
    // Construir una cuenta de ahorro y añadirla al cliente
    auto cuentaCompartida = director.construirCuentaAhorro();
    cliente.agregarCuenta(cuentaCompartida);

    // Crear un hilo para simular depósitos seguros en la cuenta compartida
    std::thread hilo1([&cuentaCompartida]() {
        // Realizar un depósito seguro
        cuentaCompartida->depositarSeguro(1000);
        // Realizar un depósito seguro con descripción
        cuentaCompartida->depositarSeguro(200, "Depósito de bonificación");
    });

    // Crear otro hilo para simular un retiro de la misma cuenta
    std::thread hilo2([&cuentaCompartida]() {
        // Realizar un retiro
        cuentaCompartida->retirar(500);
    });

    // Esperar a que los hilos terminen su ejecución
    hilo1.join();
    hilo2.join();

    // Definir una función lambda para ajustar intereses o realizar otras operaciones en las cuentas
    auto ajustarInteres = [](std::shared_ptr<Cuenta>& cuenta) {
        // ajustar los intereses o realizar otra operación
    };

    // Aplicar la función lambda a todas las cuentas del cliente
    aplicarAjusteACuentas(cliente, ajustarInteres);

    // Mostrar los saldos de todas las cuentas del cliente
    cliente.mostrarSaldos();

    return 0;
}

// Instrucción para compilar y ejecutar el programa
// exec: g++ -std=c++11 -o FinancialAccountSystem FinancialAccountSystem.cpp -pthread && ./FinancialAccountSystem
