#include <iostream>
#include <memory>

int main() {
    // Ejemplo de std::unique_ptr
    std::cout << "Ejemplo de std::unique_ptr:" << std::endl;
    std::unique_ptr<int> uniquePtr = std::make_unique<int>(42);
    std::cout << "Valor a través de uniquePtr: " << *uniquePtr << std::endl;

    // Ejemplo de std::shared_ptr
    std::cout << "\nEjemplo de std::shared_ptr:" << std::endl;
    std::shared_ptr<int> sharedPtr1 = std::make_shared<int>(10);
    std::shared_ptr<int> sharedPtr2 = sharedPtr1;
    *sharedPtr1 = 20;
    std::cout << "Valor a través de sharedPtr2: " << *sharedPtr2 << std::endl;

    // Ejemplo de std::weak_ptr
    std::cout << "\nEjemplo de std::weak_ptr:" << std::endl;
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(5);
    std::weak_ptr<int> weakPtr = sharedPtr;
    if (auto sharedPtr2 = weakPtr.lock()) {
        std::cout << "Valor a través de weakPtr: " << *sharedPtr2 << std::endl;
    } else {
        std::cout << "El objeto ya no existe." << std::endl;
    }

    return 0;
}
