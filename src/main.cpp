#include "telemetry_record.hpp"
#include "csv_reader.hpp"
#include "filter.hpp"

#include <iostream>

int main(){
    CSVReader reader;
    auto data = reader.read("data/telemetry_data.csv");

    std::cout << "Records read: " << data.size() << "\n";

    Filter filter;
    filter.applyMovingAverage(data, 3);
    std::cout << "Applied Filter"<<std::endl;
    return 0;
}