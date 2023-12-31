// CuentaEmpresarial.h
#include <memory>

#include "Usuario.h"
#include "Cuenta.h"
#ifndef CUENTAEMPRESARIAL_H
#define CUENTAEMPRESARIAL_H

class CuentaEmpresarial : public Cuenta {
public:
    CuentaEmpresarial();
    void calcularInteres(double interes) override;
};

#endif // CUENTAEMPRESARIAL_H
