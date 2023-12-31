// TarjetaCredito.h
#include <memory>

#ifndef TARJETACREDITO_H
#define TARJETACREDITO_H

#include "Cuenta.h"

class TarjetaCredito : public Cuenta {
public:
    TarjetaCredito();
    void calcularInteres(double interes) override;
};

#endif // TARJETACREDITO_H
