#ifndef LAPTOPBUILDER_HPP
#define LAPTOPBUILDER_HPP

#include "IBuilder.hpp"

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

    // Implementar métodos para marcas, CPU, monitor, impresora, etc.
};

#endif // LAPTOPBUILDER_HPP
