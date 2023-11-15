#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

class Tarjeta {
public:
    Tarjeta() : saldo(500) {}

    // Función que representa una transacción
    void transaccion(int id) {
        std::lock_guard<std::mutex> lockSaldo(mutexSaldo);  // Primer semáforo (mutex)
        
        double monto = 100;  
        saldo += monto;
        std::cout << "Transacción " << id << ": +100. Nuevo saldo: " << saldo << std::endl;

        // Actualización del registro de transacciones mientras el saldo está bloqueado
        actualizarRegistro(id);
    }

    double obtenerSaldo() const {
        return saldo;
    }

    const std::vector<int>& obtenerRegistro() const {
        return registroTransacciones;
    }

private:
    void actualizarRegistro(int id) {
        std::lock_guard<std::mutex> lockRegistro(mutexRegistro);  // Segundo semáforo (mutex) dentro del primero
        registroTransacciones.push_back(id);  // Registrar la transacción
        std::cout << "Transacción " << id << " registrada mientras se actualizaba el saldo." << std::endl;
    }

    double saldo;
    std::vector<int> registroTransacciones;
    // mutable se usa para indicar que el mutex se puede modificar en una función const
    mutable std::mutex mutexSaldo;        // Primer mutex para el saldo
    mutable std::mutex mutexRegistro;     // Segundo mutex para el registro de transacciones
};

int main() {
    Tarjeta miTarjeta;
    const int numTransacciones = 5;
    std::thread transacciones[numTransacciones];

    for (int i = 0; i < numTransacciones; i++) {
        transacciones[i] = std::thread(&Tarjeta::transaccion, &miTarjeta, i + 1);
    }

    for (int i = 0; i < numTransacciones; i++) {
        transacciones[i].join();
    }

    std::cout << "Operaciones completadas. Saldo final: " << miTarjeta.obtenerSaldo() << std::endl;
    return 0;
}

// file_name: tarjeta_transacciones_anidadas.cpp
// exec: g++ -o tarjeta_transacciones_anidadas tarjeta_transacciones_anidadas.cpp -lpthread -std=c++11 && ./tarjeta_transacciones_anidadas
