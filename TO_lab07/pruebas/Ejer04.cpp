#include <iostream>
#include <string>

// Clase UsuarioSistema representa a un usuario del sistema de una academia
class UsuarioSistema {
public:
    UsuarioSistema(const std::string& nombre) : nombre(nombre) {
        std::cout << "Constructor: " << nombre << std::endl;
    }

    // Constructor de movimiento
    UsuarioSistema(UsuarioSistema&& other) noexcept : nombre(std::move(other.nombre)) {
        std::cout << "Constructor de movimiento: " << nombre << std::endl;
    }

    // Destructor
    ~UsuarioSistema() {
        std::cout << "Destructor: " << nombre << std::endl;
    }

private:
    std::string nombre;
};

int main() {
    // Crear un objeto UsuarioSistema original
    UsuarioSistema usuario1("Usuario1");

    // Usar el constructor de movimiento para transferir los recursos de usuario1 a usuario2
    UsuarioSistema usuario2(std::move(usuario1));

    // usuario1 ya no posee recursos, se ha "movido" a usuario2
    // Acceder a usuario1 en este punto puede ser inseguro o indefinido

    return 0;
}
