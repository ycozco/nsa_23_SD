#include "CSVReader.h"
#include "DistanceCalculator.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

std::mutex distancesMutex;
std::vector<std::pair<size_t, std::pair<double, double>>> allDistances;

void CalculateDistancesFromFirst(const std::vector<DataPoint*>& dataPoints, size_t start, size_t end) {
    for (size_t j = start; j < end && j < dataPoints.size(); ++j) {
        double manhattan = DistanceCalculator::CalculateManhattanDistance(*dataPoints[0], *dataPoints[j]);
        double euclidean = DistanceCalculator::CalculateEuclideanDistance(*dataPoints[0], *dataPoints[j]);

        std::lock_guard<std::mutex> guard(distancesMutex);
        allDistances.push_back({j, {manhattan, euclidean}});
    }
}

int main() {
    CSVReader reader("ratings_s.csv");
    auto dataPoints = reader.ReadAllDataPoints();

    // Iniciar cálculos de distancias con multithreading
    std::vector<std::thread> threads;
    size_t numThreads = std::thread::hardware_concurrency();
    size_t batchSize = dataPoints.size() / numThreads;
    std::cout << "Número de hilos disponibles: " << numThreads << std::endl;
    std::cout << "Tamaño de lote: " << batchSize << std::endl;
    for (size_t i = 0; i < numThreads; ++i) {
        size_t start = i * batchSize;
        size_t end = (i + 1) * batchSize;
        if (i == numThreads - 1) {
            end = dataPoints.size(); // Asegurar que el último lote incluya todos los elementos restantes
        }
        threads.push_back(std::thread(CalculateDistancesFromFirst, std::ref(dataPoints), start, end));
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

    std::cout << "Primeras 5 distancias calculadas respecto al primer punto:" << std::endl;
    for (size_t i = 0; i < allDistances.size() && i < 5; ++i) {
        file << "Punto 1 a Punto " << allDistances[i].first + 1 
             << " - Manhattan: " << allDistances[i].second.first 
             << ", Euclidiana: " << allDistances[i].second.second << std::endl;

        std::cout << "Punto 1 a Punto " << allDistances[i].first + 1 
                  << " - Manhattan: " << allDistances[i].second.first 
                  << ", Euclidiana: " << allDistances[i].second.second << std::endl;
    }

    file.close();

    // Limpieza de memoria
    for (auto dp : dataPoints) {
        delete dp;
    }

    return 0;
}
