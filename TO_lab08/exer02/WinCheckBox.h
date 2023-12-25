// WinCheckBox.h
#ifndef WINCHECKBOX_H
#define WINCHECKBOX_H

#include "CheckBox.h"

// CheckBox concreto para Windows
class WinCheckBox : public CheckBox {
public:
    void Draw() const override {
        std::cout << "Dibujando CheckBox Windows" << std::endl;
    }
};

#endif // WINCHECKBOX_H
