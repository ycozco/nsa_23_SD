// Button.h
#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>

// Interfaz abstracta para botones
class Button {
public:
    virtual void Draw() const = 0;
    virtual ~Button() {}
};

#endif // BUTTON_H
