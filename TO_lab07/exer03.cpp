#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::vector<std::string> palabras;
    std::string palabra;

    std::cout << "Ingresa palabras (escribe 'fin' para terminar la entrada):\n";

    // Ciclo para ingresar palabras
    while (true) {
        std::cin >> palabra;
        if (palabra == "fin") {
            break;
        }
        palabras.push_back(palabra);
    }

    // Ordenar las palabras alfabéticamente utilizando std::sort() y una función lambda
    std::sort(palabras.begin(), palabras.end(), [](const std::string& a, const std::string& b) {
        return a < b;
    });

    std::cout << "\nPalabras ordenadas alfabéticamente:\n";

    // Mostrar las palabras ordenadas
    for (const std::string& palabra : palabras) {
        std::cout << palabra << " ";
    }

    std::cout << std::endl;

    return 0;
}
