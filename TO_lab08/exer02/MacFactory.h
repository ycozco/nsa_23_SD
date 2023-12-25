// MacFactory.h
#ifndef MACFACTORY_H
#define MACFACTORY_H

#include "GUIFactory.h"
#include "MacButton.h"
#include "MacCheckBox.h"
#include <iostream>

// Fábrica concreta para Mac
class MacFactory : public GUIFactory {
public:
    Button* CreateButton() const override {
        return new MacButton();
    }
    CheckBox* CreateCheckBox() const override {
        return new MacCheckBox();
    }
    void Draw() const override {
        std::cout << "Dibujando interfaz Mac" << std::endl;
    }
};

#endif // MACFACTORY_H
