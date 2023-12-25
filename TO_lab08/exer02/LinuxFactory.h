// LinuxFactory.h
#ifndef LINUXFACTORY_H
#define LINUXFACTORY_H

#include "GUIFactory.h"
#include "LinuxButton.h"
#include "LinuxCheckBox.h"
#include <iostream>

// Fábrica concreta para Linux
class LinuxFactory : public GUIFactory {
public:
    Button* CreateButton() const override {
        return new LinuxButton();
    }
    CheckBox* CreateCheckBox() const override {
        return new LinuxCheckBox();
    }
    void Draw() const override {
        std::cout << "Dibujando interfaz Linux" << std::endl;
    }
};

#endif // LINUXFACTORY_H
