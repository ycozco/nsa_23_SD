#include <iostream>
#include <cstdlib>
#include <string>

bool validarExtensionArchivo(const std::string& nombreArchivo) {
    // Obtener la posición del último punto en el nombre del archivo.
    size_t pos = nombreArchivo.find_last_of(".");
    
    // Verificar si se encontró un punto y si la extensión es "jpg", "gif" o "png".
    if (pos != std::string::npos) {
        std::string extension = nombreArchivo.substr(pos + 1);
        if (extension == "jpg" || extension == "gif" || extension == "png") {
            return true; // La extensión es válida.
        }
    }
    
    return false; // La extensión no es válida.
}

int main() {
    std::string nombres[5] = {"imagen.xyzx", "foto.png", "archivo.gif", "documento.pdf", "imagen.jpeg"};
    
    for (const auto& nombre : nombres) {
        std::cout << "Archivo: " << nombre << " - Resultado: " << (validarExtensionArchivo(nombre) ? "Valido" : "Invalido") << std::endl;
    }
    
    return 0;
}

// exec: g++ -o validar_extension_archivo validar_extension_archivo.cpp && ./validar_extension_archivo
