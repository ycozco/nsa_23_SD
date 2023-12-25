#include <iostream>
#include <string>

class MiClase {
public:
    MiClase(const std::string& valor) : dato(valor) {
        std::cout << "Constructor llamado para '" << dato << "'" << std::endl;
    }

    // Constructor de movimiento
    MiClase(MiClase&& otro) noexcept : dato(std::move(otro.dato)) {
        std::cout << "Constructor de movimiento llamado para '" << dato << "'" << std::endl;
    }

    // Función para mostrar el valor
    void mostrar() const {
        std::cout << "Valor: " << dato << std::endl;
    }

private:
    std::string dato;
};

int main() {
    // Crear una instancia de MiClase
    MiClase objeto1("Hola, mundo!");

    // Llamar al constructor de movimiento para transferir la propiedad
    MiClase objeto2(std::move(objeto1));

    // Intentar acceder a objeto1 después de la transferencia
    // Esto no debería mostrar nada ya que el objeto1 se ha movido
    std::cout << "Intentando acceder a objeto1 después de la transferencia:" << std::endl;
    objeto1.mostrar();  // No se mostrará nada

    // Mostrar el valor de objeto2
    std::cout << "Valor de objeto2:" << std::endl;
    objeto2.mostrar();

    return 0;
}
