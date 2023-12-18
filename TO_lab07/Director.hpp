#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP

#include "Builders/IBuilder.hpp"

class Director {
    IBuilder* builder;

public:
    void setBuilder(IBuilder* b) {
        builder = b;
    }

    Laptop* buildLaptop() {
        return builder->build();
    }
};

#endif // DIRECTOR_HPP
