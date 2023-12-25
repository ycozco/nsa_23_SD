// CuentaAhorro.h
#include <memory>

#ifndef CUENTAAHORRO_H
#define CUENTAAHORRO_H

#include "Cuenta.h"

class CuentaAhorro : public Cuenta {
public:
    void calcularInteres() override;
};

#endif // CUENTAAHORRO_H
