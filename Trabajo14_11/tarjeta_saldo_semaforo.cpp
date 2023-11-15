#include <iostream>
#include <thread>
#include <mutex>

// Estructura para almacenar datos de la tarjeta
class Tarjeta {
public:
    Tarjeta() : saldo(500) {}  // Inicializar el saldo

    // Función que representa una transacción
    void transaccion() {
        std::lock_guard<std::mutex> lock(mutexSaldo);  // Bloqueamos el mutex antes de acceder al saldo

        // Zona crítica - actualización del saldo
        double monto = 100;  // Este valor puede variar dependiendo de la transacción
        saldo += monto;
        std::cout << "Saldo actualizado. + 100  Nuevo saldo: " << saldo << std::endl;
    }

    double obtenerSaldo() const {
        return saldo;
    }

private:
    double saldo;
    mutable std::mutex mutexSaldo;  // Mutex para controlar el acceso al saldo
};

int main() {
    Tarjeta miTarjeta;

    // Creamos múltiples hilos para simular transacciones concurrentes
    const int numTransacciones = 5;
    std::thread transacciones[numTransacciones];

    for (int i = 0; i < numTransacciones; i++) {
        transacciones[i] = std::thread(&Tarjeta::transaccion, &miTarjeta);
    }

    // Esperamos a que todas las transacciones terminen
    for (int i = 0; i < numTransacciones; i++) {
        transacciones[i].join();
    }

    std::cout << "Operaciones completadas. Saldo final: " << miTarjeta.obtenerSaldo() << std::endl;
    return 0;
}

// file_name: tarjeta_saldo_semaforo.cpp
// how to execute: g++ -o tarjeta_saldo_semaforo tarjeta_saldo_semaforo.cpp -lpthread -std=c++11 && ./tarjeta_saldo_semaforo

