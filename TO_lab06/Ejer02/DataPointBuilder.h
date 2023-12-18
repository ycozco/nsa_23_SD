#ifndef DATAPOINTBUILDER_H
#define DATAPOINTBUILDER_H

#include "DataPoint.h"
#include <sstream>

class DataPointBuilder {
public:
    DataPoint* BuildFromCSVRow(const std::string& row) {
        std::istringstream iss(row);
        std::string token;
        std::vector<double> coords;

        while (std::getline(iss, token, ',')) {
            coords.push_back(std::stod(token));
        }

        return new DataPoint(coords);
    }
};

#endif // DATAPOINTBUILDER_H
