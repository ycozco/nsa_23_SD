// WinFactory.h
#ifndef WINFACTORY_H
#define WINFACTORY_H

#include "GUIFactory.h"
#include "WinButton.h"
#include "WinCheckBox.h"
#include <iostream>

// Fábrica concreta para Windows
class WinFactory : public GUIFactory {
public:
    Button* CreateButton() const override {
        return new WinButton();
    }
    CheckBox* CreateCheckBox() const override {
        return new WinCheckBox();
    }
    void Draw() const override {
        std::cout << "Dibujando interfaz Windows" << std::endl;
    }
};

#endif // WINFACTORY_H
