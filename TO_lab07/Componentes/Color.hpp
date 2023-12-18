#ifndef COLOR_HPP
#define COLOR_HPP

#include "IComponent.hpp"

class Color : public IComponent {
    std::string color;

public:
    Color(std::string col) : color(col) {}
    void apply() override {
        // Aplicar el color al producto
    }
};

#endif // COLOR_HPP
