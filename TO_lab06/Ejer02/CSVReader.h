#ifndef CSVREADER_H
#define CSVREADER_H

#include "DataPointBuilder.h"
#include <fstream>
#include <vector>
#include <string>

class CSVReader {
private:
    std::string filename;
    DataPointBuilder builder;

public:
    CSVReader(const std::string& file) : filename(file) {}

    std::vector<DataPoint*> ReadAllDataPoints() {
        std::vector<DataPoint*> dataPoints;
        std::ifstream file(filename);
        std::string line;

        // Omitir la cabecera si es necesario
        // std::getline(file, line);

        while (std::getline(file, line)) {
            DataPoint* dp = builder.BuildFromCSVRow(line);
            dataPoints.push_back(dp);
        }

        return dataPoints;
    }
};

#endif // CSVREADER_H
