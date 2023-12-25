// WinButton.h
#ifndef WINBUTTON_H
#define WINBUTTON_H

#include "Button.h"

// Botón concreto para Windows
class WinButton : public Button {
public:
    void Draw() const override {
        std::cout << "Dibujando Button Windows" << std::endl;
    }
};

#endif // WINBUTTON_H
