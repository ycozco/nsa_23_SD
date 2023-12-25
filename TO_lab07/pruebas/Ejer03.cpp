#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <thread>
#include <mutex>

std::mutex mtx; // Mutex para operaciones seguras de subprocesos

// Estructura de calificaciones de usuario
struct CalificacionUsuario {
    int item;
    float calificacion;
};

// Función para leer calificaciones desde un archivo CSV
std::unordered_map<int, std::vector<CalificacionUsuario>> leerCalificaciones(const std::string& archivo) {
    std::unordered_map<int, std::vector<CalificacionUsuario>> calificaciones;
    std::ifstream archivoCSV(archivo);
    std::string linea, token;

    while (std::getline(archivoCSV, linea)) {
        std::istringstream ss(linea);
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        int usuario = std::stoi(tokens[0]);
        int item = std::stoi(tokens[1]);
        float calificacion = std::stof(tokens[2]);
        if (calificacion != 0.0f) { // No considerar calificaciones con valor 0
            calificaciones[usuario].push_back({item, calificacion});
        }
    }

    return calificaciones;
}

// Función para calcular la distancia de Manhattan entre dos conjuntos de calificaciones de usuarios
float distanciaManhattan(const std::vector<CalificacionUsuario>& calificacionesUsuario1, const std::vector<CalificacionUsuario>& calificacionesUsuario2) {
    float distancia = 0.0;
    for (const auto& calificacion1 : calificacionesUsuario1) {
        for (const auto& calificacion2 : calificacionesUsuario2) {
            if (calificacion1.item == calificacion2.item) {
                distancia += std::abs(calificacion1.calificacion - calificacion2.calificacion);
                break;
            }
        }
    }
    return distancia;
}

// Función para calcular la distancia Euclidiana entre dos conjuntos de calificaciones de usuarios
float distanciaEuclidiana(const std::vector<CalificacionUsuario>& calificacionesUsuario1, const std::vector<CalificacionUsuario>& calificacionesUsuario2) {
    float distancia = 0.0;
    for (const auto& calificacion1 : calificacionesUsuario1) {
        for (const auto& calificacion2 : calificacionesUsuario2) {
            if (calificacion1.item == calificacion2.item) {
                distancia += std::pow(calificacion1.calificacion - calificacion2.calificacion, 2);
                break;
            }
        }
    }
    return std::sqrt(distancia);
}

// Función para encontrar los 3 usuarios más similares a un usuario dado
std::vector<int> encontrarUsuariosSimilares(const int usuarioObjetivo, const std::unordered_map<int, std::vector<CalificacionUsuario>>& calificaciones) {
    std::vector<std::pair<int, float>> puntuacionesSimilitud;

    for (const auto& calificacionesUsuario : calificaciones) {
        if (calificacionesUsuario.first != usuarioObjetivo) {
            float distancia = distanciaManhattan(calificaciones.at(usuarioObjetivo), calificacionesUsuario.second);
            puntuacionesSimilitud.push_back({calificacionesUsuario.first, distancia});
        }
    }

    std::sort(puntuacionesSimilitud.begin(), puntuacionesSimilitud.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    std::vector<int> usuariosSimilares;
    int count = 0;
    for (const auto& pair : puntuacionesSimilitud) {
        if (count >= 3) break;
        usuariosSimilares.push_back(pair.first);
        count++;
    }
    return usuariosSimilares;
}

int main() {
    const std::string archivo = "ratings_s.csv";
    auto calificaciones = leerCalificaciones(archivo);

    // Calcular la distancia de Manhattan entre Usuario 20 y 32 en un hilo
    std::thread hiloManhattan([&] {
        float distanciaManhattan20_32 = distanciaManhattan(calificaciones[20], calificaciones[32]);
        mtx.lock();
        std::cout << "a).- Distancia de Manhattan entre Usuario 20 y 32: " << distanciaManhattan20_32 << std::endl;
        mtx.unlock();
    });

    // Calcular la distancia Euclidiana entre Usuario 20 y 32 en un hilo
    std::thread hiloEuclidiana([&] {
        float distanciaEuclidiana20_32 = distanciaEuclidiana(calificaciones[20], calificaciones[32]);
        mtx.lock();
        std::cout << "b).- Distancia Euclidiana entre Usuario 20 y 32: " << distanciaEuclidiana20_32 << std::endl;
        mtx.unlock();
    });

    // Encontrar los 3 usuarios más similares al Usuario 57 en preferencias (sin considerar calificaciones 0) en un hilo
    std::thread hiloUsuariosSimilares([&] {
        auto usuariosSimilares57 = encontrarUsuariosSimilares(57, calificaciones);
        mtx.lock();
        std::cout << "c).- Para el Usuario 57, los 3 usuarios más cercanos en preferencias (sin considerar calificaciones 0): ";
        for (int usuario : usuariosSimilares57) {
            std::cout << usuario << " ";
        }
        std::cout << std::endl;
        mtx.unlock();
    });

    // Esperar a que los hilos terminen
    hiloManhattan.join();
    hiloEuclidiana.join();
    hiloUsuariosSimilares.join();

    return 0;
}
