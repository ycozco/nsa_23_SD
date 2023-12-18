#ifndef IBUILDER_HPP
#define IBUILDER_HPP

#include "IComponent.hpp"

class IBuilder {
public:
    virtual ~IBuilder() {}
    virtual void buildParteA() const = 0;
    virtual void buildParteB() const = 0;
    virtual void buildParteC() const = 0;
    virtual void withColor(std::string color) = 0;
    virtual void withBrand(std::string brand) = 0;
    virtual void withCPU(std::string cpuType) = 0;
    virtual void withMonitor(std::string monitorType) = 0;
    virtual void withPrinter(std::string printerType) = 0;
    virtual Laptop* build() = 0;
    virtual IBuilder* setColor(std::string color) = 0;
    // Puedes seguir agregando características aquí.
};
