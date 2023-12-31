// CuentaPluss.h
#include <memory>

#ifndef CUENTAPLUSS_H
#define CUENTAPLUSS_H

#include "Cuenta.h"
#include "Usuario.h"

class CuentaPluss : public Cuenta {
public:
    CuentaPluss();
    void calcularInteres(double interes) override;
};

#endif // CUENTAPLUSS_H
