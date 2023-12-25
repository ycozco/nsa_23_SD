// TarjetaCredito.h
#include <memory>

#ifndef TARJETACREDITO_H
#define TARJETACREDITO_H

#include "Cuenta.h"

class TarjetaCredito : public Cuenta {
public:
    void calcularInteres() override;
};

#endif // TARJETACREDITO_H
