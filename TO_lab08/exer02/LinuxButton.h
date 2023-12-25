// LinuxButton.h
#ifndef LINUXBUTTON_H
#define LINUXBUTTON_H

#include "Button.h"

// Botón concreto para Linux
class LinuxButton : public Button {
public:
    void Draw() const override {
        std::cout << "Dibujando Button Linux" << std::endl;
    }
};

#endif // LINUXBUTTON_H
