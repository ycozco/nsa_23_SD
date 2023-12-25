// GUIFactory.h
#ifndef GUIFACTORY_H
#define GUIFACTORY_H

#include "Button.h"
#include "CheckBox.h"

// Interfaz abstracta para las fábricas de elementos de GUI
class GUIFactory {
public:
    virtual Button* CreateButton() const = 0;
    virtual CheckBox* CreateCheckBox() const = 0;
    virtual void Draw() const = 0;
    virtual ~GUIFactory() {}
};

#endif // GUIFACTORY_H
