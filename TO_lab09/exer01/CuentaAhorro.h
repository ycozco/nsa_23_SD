// CuentaAhorro.h
#include <memory>
#include "Usuario.h"
#include "Cuenta.h"
#ifndef CUENTAAHORRO_H
#define CUENTAAHORRO_H

#include "Cuenta.h"

class CuentaAhorro : public Cuenta {
public:

    CuentaAhorro();
    void calcularInteres(double interes) override;
};

#endif // CUENTAAHORRO_H
