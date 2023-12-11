#include <iostream>
#include <cstdio>
#include <array>
#include <string>

// Función para validar un email utilizando el comando 'awk' en el sistema.
bool validarEmail(const std::string& email) {
    // Crear un comando 'awk' para validar el email usando una expresión regular.
    std::string cmd = "echo '" + email + "' | awk '";
    cmd += "/^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,6}$/ {exit 0} {exit 1}'";

    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return false;

    // Leer la salida del comando 'awk' línea por línea.
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    // Devolver verdadero si 'awk' sale con un código de salida 0 (éxito), falso en caso contrario.
    return pclose(pipe) == 0;
}

int main() {
    // Array de strings que contienen direcciones de correo electrónico.
    std::string emails[5] = {"test@example.com", "invalid-email", "user.name@domain.com", "user@domain", "name@domain.co"};
    
    // Iterar a través de los emails y validarlos.
    for (const auto& email : emails) {
        // Imprimir el email y el resultado de la validación.
        std::cout << "Email: " << email << " - Resultado: " << (validarEmail(email) ? "Valido" : "Invalido") << std::endl;
    }
    return 0;
}

// Para compilar y ejecutar: g++ -o validar_email validar_email.cpp && ./validar_email
