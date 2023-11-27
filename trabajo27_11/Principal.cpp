#include <iostream>
#include <thread>

// Clase Tarea que representa la tarea que se ejecutará en un thread
class Tarea {
    std::string name;

public:
    Tarea(std::string name) : name(name) {}

    // Operador que define la tarea del thread
    void operator()() {
        for (int i = 0; i < 10; ++i) {
            std::cout << name << ": " << i << std::endl;
        }
    }
};

// Clase Principal que contiene el método main
class Principal {
public:
    static void main() {
        // Crear las tareas
        Tarea tarea1("hilo1");
        Tarea tarea2("hilo2");

        // Crear y ejecutar los threads
        std::thread hilo1(tarea1);
        std::thread hilo2(tarea2);

        // Esperar a que los threads terminen
        hilo1.join();
        hilo2.join();
    }
};

int main() {
    // Ejecutar el método main de la clase Principal
    Principal::main();
    return 0;
}

// file_name: Principal.cpp
// exec: g++ -o Principal Principal.cpp -pthread && ./Principal
