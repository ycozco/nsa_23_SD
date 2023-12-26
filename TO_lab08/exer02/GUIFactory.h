// Application.cpp
#include "GUIFactory.h"
#include "WinFactory.h"
#include "MacFactory.h"
#include "LinuxFactory.h"
#include <iostream>

// Función para demostrar el uso de las fábricas
void Application(const GUIFactory& factory) {
    Button* button = factory.CreateButton();
    CheckBox* checkbox = factory.CreateCheckBox();
    button->Draw();
    checkbox->Draw();
    delete button;
    delete checkbox;
    factory.Draw();
}

int main() {
    std::cout << "Cliente: Windows" << std::endl;
    WinFactory winFactory;
    Application(winFactory);

    std::cout << std::endl << "Cliente: Mac" << std::endl;
    MacFactory macFactory;
    Application(macFactory);

    std::cout << std::endl << "Cliente: Linux" << std::endl;
    LinuxFactory linuxFactory;
    Application(linuxFactory);

    return 0;
}
// file name: Application.cpp
// g++ -std=c++11 Application.cpp -o app && ./app