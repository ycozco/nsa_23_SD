#ifndef COLOR_HPP
#define COLOR_HPP

#include "IComponent.hpp"
#include <string>

class Color : public IComponent {
    std::string color;

public:
    Color(std::string col) : color(col) {}

    void apply() override {
        // Implementación específica para aplicar el color
    }
};

#endif // COLOR_HPP
