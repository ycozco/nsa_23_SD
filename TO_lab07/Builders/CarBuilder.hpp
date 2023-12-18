#ifndef CARBUILDER_HPP
#define CARBUILDER_HPP

#include "IBuilder.hpp"

class CarBuilder : public IBuilder {
    IComponent* getComponent() const override {
        // Devuelve una instancia de un componente del automóvil
        return nullptr;
    }
};

#endif // CARBUILDER_HPP
