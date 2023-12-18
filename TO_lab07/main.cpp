#include "Director.hpp"
#include "Builders/LaptopBuilder.hpp"

int main() {
    Director director;
    LaptopBuilder builder;

    director.setBuilder(&builder);
    Laptop* laptop = director.buildLaptop()
        ->setColor("Red")
        // Llamar a los métodos para marcas, CPU, monitor, impresora, etc.
        ->build();

    laptop->showConfiguration();

    delete laptop;
    return 0;
}
