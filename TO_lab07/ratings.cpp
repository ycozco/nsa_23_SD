#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <thread>
#include <mutex>
#include <algorithm>

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
        calificaciones[usuario].push_back({item, calificacion});
    }

    return calificaciones;
}

// Función para calcular la distancia de Manhattan
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

// Función para calcular la distancia Euclidiana
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
    for (int i = 0; i < 3 && i < puntuacionesSimilitud.size(); ++i) {
        usuariosSimilares.push_back(puntuacionesSimilitud[i].first);
    }
    return usuariosSimilares;
}

int main() {
    const std::string archivo = "calificaciones.csv";
    auto calificaciones = leerCalificaciones(archivo);

    // Cálculo en paralelo usando hilos
    std::thread hiloManhattan([&] {
        float distancia = distanciaManhattan(calificaciones[20], calificaciones[32]);
        mtx.lock();
        std::cout << "a).- Distancia de Manhattan entre Usuario 20 y 32: " << distancia << std::endl;
        mtx.unlock();
    });

    std::thread hiloEuclidiana([&] {
        float distancia = distanciaEuclidiana(calificaciones[20], calificaciones[32]);
        mtx.lock();
        std::cout << "b).- Distancia Euclidiana entre Usuario 20 y 32: " << distancia << std::endl;
        mtx.unlock();
    });

    std::thread hiloUsuariosSimilares([&] {
        auto usuariosSimilares = encontrarUsuariosSimilares(57, calificaciones);
        mtx.lock();
        std::cout << "c).- Para el Usuario 57, los 3 usuarios más cercanos en preferencias (sin considerar calificaciones 0): ";
        for (int usuario : usuariosSimilares) {
            std::cout << usuario << " ";
        }
        std::cout << std::endl;
        mtx.unlock();
    });

    hiloManhattan.join();
    hiloEuclidiana.join();
    hiloUsuariosSimilares.join();

    return 0;
}
