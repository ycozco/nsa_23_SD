#ifndef LAPTOP_HPP
#define LAPTOP_HPP

#include "../Components/IComponent.hpp"
#include <vector>
#include <string>

class Laptop {
    std::vector<IComponent*> components;
    std::string color;
    // Campos adicionales para marcas, CPU, monitor, impresora, etc.

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

    // Métodos adicionales para establecer marcas, CPU, monitor, impresora, etc.

    void showConfiguration() const {
        // Implementación del método para mostrar la configuración de la laptop
    }
};

#endif // LAPTOP_HPP
