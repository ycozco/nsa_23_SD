#ifndef ACCOUNTBUILDER_HPP
#define ACCOUNTBUILDER_HPP

#include "IBuilder.hpp"

class AccountBuilder : public IBuilder {
    IComponent* getComponent() const override {
        // Devuelve una instancia de un componente de cuenta bancaria
        return nullptr;
    }
};

#endif // ACCOUNTBUILDER_HPP
