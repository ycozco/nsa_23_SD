#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

/**
 * Clase LectorEscritor para manejar el problema lector-escritor.
 * Permite múltiples lectores o un único escritor acceder a un recurso compartido.
 */
class LectorEscritor {
public:
    LectorEscritor() : lectores(0), escritores(0) {}

    // Método para simular la lectura del recurso compartido.
    void leer(int id) {
        std::unique_lock<std::mutex> lock(mutex);
        leer_cond.wait(lock, [this]() { return escritores == 0; });

        lectores++;
        lock.unlock();

        std::cout << "Lector " << id << " leyendo. Lectores activos: " << lectores << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simular lectura

        lock.lock();
        lectores--;
        std::cout << "Lector " << id << " ha terminado de leer. Lectores activos: " << lectores << std::endl;

        escribir_cond.notify_all();
    }

    // Método para simular la escritura en el recurso compartido.
    void escribir(int id) {
        std::unique_lock<std::mutex> lock(mutex);
        escribir_cond.wait(lock, [this]() { return lectores == 0 && escritores == 0; });

        escritores++;
        lock.unlock();

        std::cout << "Escritor " << id << " escribiendo." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simular escritura

        lock.lock();
        escritores--;
        std::cout << "Escritor " << id << " ha terminado de escribir." << std::endl;

        leer_cond.notify_all();
        escribir_cond.notify_all();
    }

private:
    std::mutex mutex;
    std::condition_variable leer_cond;
    std::condition_variable escribir_cond;
    int lectores;
    int escritores;
};

int main() {
    LectorEscritor recurso;
    std::vector<std::thread> hilos;

    // Crear algunos lectores y escritores
    for (int i = 0; i < 3; ++i) {
        hilos.emplace_back(&LectorEscritor::leer, &recurso, i);
        hilos.emplace_back(&LectorEscritor::escribir, &recurso, i);
    }

    for (auto& hilo : hilos) {
        hilo.join();
    }

    return 0;
}

// file_name: lector_escritor_problema_mejorado.cpp
// exec: g++ -o lector_escritor_mejorado lector_escritor_problema_mejorado.cpp -lpthread -std=c++11 && ./lector_escritor_mejorado
