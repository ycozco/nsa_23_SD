// MacCheckBox.h
#ifndef MACCHECKBOX_H
#define MACCHECKBOX_H

#include "CheckBox.h"

// CheckBox concreto para Mac
class MacCheckBox : public CheckBox {
public:
    void Draw() const override {
        std::cout << "Dibujando CheckBox Mac" << std::endl;
    }
};

#endif // MACCHECKBOX_H
