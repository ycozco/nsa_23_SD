#include <iostream>
#include <memory>
#include <thread>

// Función para imprimir un mensaje y el número de referencia
void imprimirReferencia(const std::string& mensaje, int& referencia) {
    std::cout << mensaje << " Referencia: " << referencia << std::endl;
}

int main() {
    // Ejemplo de std::shared_ptr
    std::cout << "Ejemplo de std::shared_ptr:" << std::endl;
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(42);
    int referenciaShared = 1;

    // Crear un hilo para imprimir la referencia compartida
    std::thread threadShared(imprimirReferencia, "Shared", std::ref(referenciaShared));

    // Crear un hilo para acceder al std::shared_ptr
    std::thread threadAccessShared([&] {
        std::cout << "Acceso a std::shared_ptr: " << *sharedPtr << std::endl;
        referenciaShared++;  // Incrementa la referencia compartida
    });

    // Esperar a que ambos hilos terminen
    threadShared.join();
    threadAccessShared.join();

    // Ejemplo de std::unique_ptr
    std::cout << "\nEjemplo de std::unique_ptr:" << std::endl;
    std::unique_ptr<double> uniquePtr = std::make_unique<double>(3.14);
    int referenciaUnique = 1;

    // Crear un hilo para imprimir la referencia única
    std::thread threadUnique(imprimirReferencia, "Unique", std::ref(referenciaUnique));

    // Intentar crear otro std::unique_ptr al mismo recurso (esto no funcionará)
    // std::unique_ptr<double> otroUniquePtr = uniquePtr; // Esto dará un error en tiempo de compilación

    // Esperar a que el hilo termine
    threadUnique.join();

    // Ejemplo de std::weak_ptr
    std::cout << "\nEjemplo de std::weak_ptr:" << std::endl;
    std::shared_ptr<int> strongPtr = std::make_shared<int>(100);
    std::weak_ptr<int> weakPtr = strongPtr;  // Crear un std::weak_ptr desde un std::shared_ptr

    int referenciaWeak = 1;

    // Crear un hilo para imprimir la referencia débil
    std::thread threadWeak(imprimirReferencia, "Weak", std::ref(referenciaWeak));

    // Comprobar si el std::weak_ptr sigue siendo válido
    if (!weakPtr.expired()) {
        std::shared_ptr<int> sharedFromWeak = weakPtr.lock(); // Convertir el std::weak_ptr en std::shared_ptr
        std::cout << "Acceso desde std::weak_ptr: " << *sharedFromWeak << std::endl;
        referenciaWeak++;  // Incrementa la referencia débil
    } else {
        std::cout << "El recurso al que apunta std::weak_ptr ya no es válido." << std::endl;
    }

    // Esperar a que el hilo termine
    threadWeak.join();

    return 0;
}
