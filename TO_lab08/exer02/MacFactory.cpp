// MacFactory.cpp
#include "MacFactory.h"

// Implementación de los métodos de creación específicos de Mac.
Button* MacFactory::CreateButton() const {
    return new MacButton(); // Crea un botón de Mac.
}

CheckBox* MacFactory::CreateCheckBox() const {
    return new MacCheckBox(); // Crea un checkbox de Mac.
}

void MacFactory::Draw() const {
    // Este método podría ser utilizado para dibujar la interfaz de usuario de Mac,
    // pero en este ejemplo, solo imprimirá un mensaje.
    std::cout << "Dibujando interfaz de usuario de Mac." << std::endl;
}
