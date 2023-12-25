#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Usuario {
    string nombre;
    int edad;
};

int main() {
    vector<Usuario> usuarios;

    // Solicitar al usuario ingresar datos de usuarios
    cout << "Ingrese datos de usuarios (nombre edad), ingrese 'fin' para finalizar:" << endl;
    string nombre;
    int edad;
    
    while (true) {
        cin >> nombre;
        if (nombre == "fin") {
            break;
        }
        
        cin >> edad;
        
        Usuario usuario;
        usuario.nombre = nombre;
        usuario.edad = edad;
        
        usuarios.push_back(usuario);
    }

    // Usar una función lambda y sort() para ordenar el vector por edad
    sort(usuarios.begin(), usuarios.end(), [](const Usuario& a, const Usuario& b) {
        return a.edad < b.edad;
    });

    // Mostrar la lista de usuarios ordenada por edad
    cout << "Lista de usuarios ordenada por edad:" << endl;
    for (const Usuario& u : usuarios) {
        cout << "Nombre: " << u.nombre << ", Edad: " << u.edad << endl;
    }

    return 0;
}
