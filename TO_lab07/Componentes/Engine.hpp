#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "IComponent.hpp"

class Engine : public IComponent {
public:
    void configure() override {
        // Configuración del motor
    }
};

#endif // ENGINE_HPP
