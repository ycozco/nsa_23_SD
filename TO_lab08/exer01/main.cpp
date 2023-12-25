#include "FabricaRecetas.cpp"
#include <iostream>

int main() {
    int tipo;
    std::cout << "Ingrese un tipo de receta (1 a 5) o '0' para salir: ";
    while (std::cin >> tipo && tipo != 0) {
        Receta* receta = FabricaRecetas::crearReceta(tipo);
        // La memoria se limpia en la fábrica después de mostrar la receta, no se necesita hacer aquí.
        delete receta; // Asegúrate de que cada clase derivada de Receta tenga un destructor apropiado.
    }
    std::cout << "Saliendo de la aplicación de recetas." << std::endl;
    return 0;
}

// file_name: main.cpp
// exec: g++ -o recipe_app FabricaRecetas.cpp Receta.cpp main.cpp && ./recipe_app
