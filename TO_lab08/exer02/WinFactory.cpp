// WinFactory.cpp
#include "WinFactory.h"

// Implementación de los métodos de creación específicos de Windows.
Button* WinFactory::CreateButton() const {
    return new WinButton(); // Crea un botón de Windows.
}

CheckBox* WinFactory::CreateCheckBox() const {
    return new WinCheckBox(); // Crea un checkbox de Windows.
}

void WinFactory::Draw() const {
    // Este método podría ser utilizado para dibujar la interfaz de usuario de Windows,
    // pero en este ejemplo, solo imprimirá un mensaje.
    std::cout << "Dibujando interfaz de usuario de Windows." << std::endl;
}
