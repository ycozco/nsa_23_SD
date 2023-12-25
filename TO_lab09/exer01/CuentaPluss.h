// CuentaPluss.h
#include <memory>

#ifndef CUENTAPLUSS_H
#define CUENTAPLUSS_H

#include "Cuenta.h"

class CuentaPluss : public Cuenta {
public:
    void calcularInteres() override;
};

#endif // CUENTAPLUSS_H
