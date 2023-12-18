#include "LinkedList.h"
#include <thread>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>

std::mutex cout_mutex; // Mutex para controlar la impresión en consola.

// Genera un número aleatorio entre min y max.
int getRandomNumber(int min, int max) {
    static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

void funcionThreadEliminar(LinkedList<int>& lista) {
    for (int i = 0; i < 10; ++i) {
        int num = getRandomNumber(1, 100);
        if (lista.remove(num)) {
            std::lock_guard<std::mutex> guard(cout_mutex);
            std::cout << "Eliminando: " << num << std::endl;
        } else {
            std::lock_guard<std::mutex> guard(cout_mutex);
            std::cout << "No se eliminó: " << num << std::endl;
        }
    }
}

void funcionThreadInsertar(LinkedList<int>& lista) {
    for (int i = 0; i < 10; ++i) {
        int num = getRandomNumber(1, 100);
        lista.insert(num);
        std::lock_guard<std::mutex> guard(cout_mutex);
        std::cout << "Insertando: " << num << std::endl;
    }
}

void funcionThreadBuscar(LinkedList<int>& lista) {
    for (int i = 0; i < 10; ++i) {
        int num = getRandomNumber(1, 100);
        if (lista.find(num)) {
            std::lock_guard<std::mutex> guard(cout_mutex);
            std::cout << "Buscado: " << num << std::endl;
        } else {
            std::lock_guard<std::mutex> guard(cout_mutex);
            std::cout << "No encontrado: " << num << std::endl;
        }
    }
}

void funcionThreadModificar(LinkedList<int>& lista) {
    for (int i = 0; i < 10; ++i) {
        int oldNum = getRandomNumber(1, 100);
        int newNum = getRandomNumber(1, 100);
        if (lista.update(oldNum, newNum)) {
            std::lock_guard<std::mutex> guard(cout_mutex);
            std::cout << "Modificando " << oldNum << " a " << newNum << std::endl;
        } else {
            std::lock_guard<std::mutex> guard(cout_mutex);
            std::cout << "No se encontró: " << oldNum << std::endl;
        }
    }
}

int main() {
    LinkedList<int> lista;

    // Inicializar la lista con algunos valores.
    for (int i = 0; i < 20; ++i) {
        lista.insert(getRandomNumber(1, 100));
    }

    // Mostrar la lista antes de las operaciones.
    lista.display();

    // Crear y ejecutar los threads.
    std::thread threadEliminar(funcionThreadEliminar, std::ref(lista));
    std::thread threadInsertar(funcionThreadInsertar, std::ref(lista));
    std::thread threadBuscar(funcionThreadBuscar, std::ref(lista));
    std::thread threadModificar(funcionThreadModificar, std::ref(lista));

    // Esperar a que los threads terminen.
    threadEliminar.join();
    threadInsertar.join();
    threadBuscar.join();
    threadModificar.join();

    // Mostrar la lista después de las operaciones.
    lista.display();

    return 0;
}

// file_name: ConcurrentLinkedList.cpp
// exec: g++ -o ConcurrentLinkedList ConcurrentLinkedList.cpp && ./ConcurrentLinkedList


// file_name: main.cpp
// exec: g++ -o ConcurrentLinkedList main.cpp -lpthread && ./ConcurrentLinkedList
