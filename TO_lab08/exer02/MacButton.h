// MacButton.h
#ifndef MACBUTTON_H
#define MACBUTTON_H

#include "Button.h"

// Botón concreto para Mac
class MacButton : public Button {
public:
    void Draw() const override {
        std::cout << "Dibujando Button Mac" << std::endl;
    }
};

#endif // MACBUTTON_H
