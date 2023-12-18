#ifndef DISTANCECALCULATOR_H
#define DISTANCECALCULATOR_H

#include "DataPoint.h"
#include <cmath>

class DistanceCalculator {
public:
    static double CalculateManhattanDistance(const DataPoint& pointA, const DataPoint& pointB) {
        const auto& coordsA = pointA.GetCoordinates();
        const auto& coordsB = pointB.GetCoordinates();
        double distance = 0.0;
        for (size_t i = 0; i < coordsA.size(); ++i) {
            distance += std::abs(coordsA[i] - coordsB[i]);
        }
        return distance;
    }

    static double CalculateEuclideanDistance(const DataPoint& pointA, const DataPoint& pointB) {
        const auto& coordsA = pointA.GetCoordinates();
        const auto& coordsB = pointB.GetCoordinates();
        double sum = 0.0;
        for (size_t i = 0; i < coordsA.size(); ++i) {
            sum += std::pow(coordsA[i] - coordsB[i], 2);
        }
        return std::sqrt(sum);
    }
};

#endif // DISTANCECALCULATOR_H
