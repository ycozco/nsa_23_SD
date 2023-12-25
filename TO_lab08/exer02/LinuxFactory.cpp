// LinuxFactory.cpp
#include "LinuxFactory.h"
#include "LinuxButton.h"
#include "LinuxCheckBox.h"

// Implementación del método CreateButton específico de Linux.
Button* LinuxFactory::CreateButton() const {
    return new LinuxButton(); // Crea un botón de Linux.
}

// Implementación del método CreateCheckBox específico de Linux.
CheckBox* LinuxFactory::CreateCheckBox() const {
    return new LinuxCheckBox(); // Crea un checkbox de Linux.
}

// Implementación del método Draw para la fábrica de Linux.
void LinuxFactory::Draw() const {
    // Este método podría ser utilizado para dibujar la interfaz de usuario de Linux,
    // pero en este ejemplo, solo imprimirá un mensaje.
    std::cout << "Dibujando interfaz de usuario de Linux." << std::endl;
}
