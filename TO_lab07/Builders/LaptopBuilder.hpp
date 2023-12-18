#ifndef LAPTOPBUILDER_HPP
#define LAPTOPBUILDER_HPP

#include "IBuilder.hpp"
#include "../Products/Laptop.hpp"

class LaptopBuilder : public IBuilder {
    Laptop* laptop;

public:
    LaptopBuilder() : laptop(new Laptop()) {}

    ~LaptopBuilder() {
        delete laptop;
    }

    Laptop* build() override {
        return laptop;
    }

    IBuilder* setColor(std::string color) override {
        laptop->setColor(color);
        return this;
    }

    // Implementaciones adicionales para otros métodos como setBrand, setCPU, etc.
};

#endif // LAPTOPBUILDER_HPP
