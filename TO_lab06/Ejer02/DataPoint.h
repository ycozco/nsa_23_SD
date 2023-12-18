#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <vector>
#include <string>

class DataPoint {
private:
    std::vector<double> coordinates;

public:
    DataPoint(const std::vector<double>& coords) : coordinates(coords) {}
    const std::vector<double>& GetCoordinates() const { return coordinates; }
};

#endif // DATAPOINT_H
