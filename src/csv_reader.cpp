#include "csv_reader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<TelemetryRecord> CSVReader::read(const std::string& file_path){
    std::vector<TelemetryRecord> data;
    std::ifstream file(file_path);

    if(!file.is_open()){
        std::cerr << "Error: Could not open file\n";
        return data;
    }

    std::string line;
    
    //skip header
    std::getline(file, line);

    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string field;

        TelemetryRecord record{};
        bool parse_error = false;

        try{
            //timestamp
            std::getline(ss, field, ',');
            record.timestamp = std::stoll(field);

            //temp
            std::getline(ss, field, ',');
            record.temp_c = std::stod(field);

            //pressure
            std::getline(ss, field, ',');
            record.pressure_kpa = std::stod(field);

            //altitude
            std::getline(ss, field, ',');
            record.altitude_m = std::stod(field);

            //velocity
            std::getline(ss, field, ',');
            record.velocity_mps = std::stod(field);

            //vibration
            std::getline(ss, field, ',');
            record.vibration_g = std::stod(field);

            //accel
            std::getline(ss, field, ',');
            record.accel_g = std::stod(field);
        } catch (...){
            parse_error = true;
        }

        if (parse_error){
            record.valid=false;
        }

        data.push_back(record);
    }
    return data;
}