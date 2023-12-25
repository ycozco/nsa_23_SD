// CuentaEmpresarial.h
#include <memory>

#ifndef CUENTAEMPRESARIAL_H
#define CUENTAEMPRESARIAL_H

#include "Cuenta.h"

class CuentaEmpresarial : public Cuenta {
public:
    void calcularInteres() override;
};

#endif // CUENTAEMPRESARIAL_H
