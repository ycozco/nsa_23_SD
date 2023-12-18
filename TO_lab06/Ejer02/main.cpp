#include "CSVReader.h"
#include "DistanceCalculator.h"
#include <thread>
#include <iostream>
#include <fstream>
#include <mutex>
#include <vector>
#include <algorithm>

std::mutex distancesMutex;
std::vector<std::pair<std::pair<size_t, size_t>, std::pair<double, double>>> allDistances;

void CalculateDistances(const std::vector<DataPoint*>& dataPoints, size_t start, size_t end) {
    for (size_t i = start; i < end && i < dataPoints.size(); ++i) {
        for (size_t j = i + 1; j < dataPoints.size(); ++j) {
            double manhattan = DistanceCalculator::CalculateManhattanDistance(*dataPoints[i], *dataPoints[j]);
            double euclidean = DistanceCalculator::CalculateEuclideanDistance(*dataPoints[i], *dataPoints[j]);

            std::lock_guard<std::mutex> guard(distancesMutex);
            allDistances.push_back({{i, j}, {manhattan, euclidean}});
        }
    }
}

int main() {
    CSVReader reader("ratings_s.csv");
    auto dataPoints = reader.ReadAllDataPoints();

    // Iniciar cálculos de distancias con multithreading
    std::vector<std::thread> threads;
    size_t batchSize = dataPoints.size() / 4;
    for (int i = 0; i < 4; ++i) {
        threads.push_back(std::thread(CalculateDistances, std::ref(dataPoints), i * batchSize, (i + 1) * batchSize));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Ordenar por distancia de Manhattan
    std::sort(allDistances.begin(), allDistances.end(), [](const auto& a, const auto& b) {
        return a.second.first < b.second.first;
    });

    // Escribir todas las distancias en un archivo y mostrar las primeras 5 en consola
    std::ofstream file("distancias_calculadas.txt");
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para escribir." << std::endl;
        return 1;
    }

    std::cout << "Primeras 5 distancias calculadas:" << std::endl;
    for (size_t i = 0; i < allDistances.size(); ++i) {
        file << "Puntos (" << allDistances[i].first.first << ", " << allDistances[i].first.second 
             << ") - Manhattan: " << allDistances[i].second.first 
             << ", Euclidiana: " << allDistances[i].second.second << std::endl;

        if (i < 5) {
            std::cout << "Puntos (" << allDistances[i].first.first << ", " << allDistances[i].first.second 
                      << ") - Manhattan: " << allDistances[i].second.first 
                      << ", Euclidiana: " << allDistances[i].second.second << std::endl;
        }
    }

    file.close();

    // Limpieza de memoria
    for (auto dp : dataPoints) {
        delete dp;
    }

    return 0;
}
