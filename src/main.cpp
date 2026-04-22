#include "telemetry_record.hpp"
#include "csv_reader.hpp"

#include <iostream>

int main(){
    CSVReader reader;
    auto data = reader.read("data/telemetry_data.csv");

    std::cout << "Records read: " << data.size() << "\n";

    return 0;
}