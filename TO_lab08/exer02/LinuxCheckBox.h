// LinuxCheckBox.h
#ifndef LINUXCHECKBOX_H
#define LINUXCHECKBOX_H

#include "CheckBox.h"

// CheckBox concreto para Linux
class LinuxCheckBox : public CheckBox {
public:
    void Draw() const override {
        std::cout << "Dibujando CheckBox Linux" << std::endl;
    }
};

#endif // LINUXCHECKBOX_H
