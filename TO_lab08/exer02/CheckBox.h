// CheckBox.h
#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <iostream>

// Interfaz abstracta para checkboxes
class CheckBox {
public:
    virtual void Draw() const = 0;
    virtual ~CheckBox() {}
};

#endif // CHECKBOX_H
