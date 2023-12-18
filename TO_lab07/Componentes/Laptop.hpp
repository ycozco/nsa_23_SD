#ifndef LAPTOP_HPP
#define LAPTOP_HPP

#include "../Components/IComponent.hpp"
#include <vector>
#include <string>

class Laptop {
    std::vector<IComponent*> components;
    std::string color;
    // Agregar campos para marcas, CPU, monitor, impresora, etc.

public:
    ~Laptop() {
        for (auto comp : components) {
            delete comp;
        }
    }

    void addComponent(IComponent* component) {
        components.push_back(component);
    }

    void setColor(const std::string& col) {
        color = col;
    }

    // Implementar métodos para establecer marcas, CPU, monitor, impresora, etc.

    void showConfiguration() const {
        // Mostrar la configuración de la laptop aquí
    }
};

#endif // LAPTOP_HPP
