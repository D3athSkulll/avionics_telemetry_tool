#include "csv_reader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <limits>
#include <cctype>
#include <algorithm>

std::string trim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

double parseValue(std::string field) {
    field = trim(field);

    if (field.empty() || field == "NaN" || field == "null") {
        return std::numeric_limits<double>::quiet_NaN();
    }

    try {
        return std::stod(field);
    } catch (...) {
        return std::numeric_limits<double>::quiet_NaN();
    }
}

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

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
    
        TelemetryRecord record{};
    
        std::getline(ss, field, ',');
        record.timestamp = std::stoll(field);
    
        std::getline(ss, field, ',');
        record.temp_c = parseValue(field);
    
        std::getline(ss, field, ',');
        record.pressure_kpa = parseValue(field);
    
        std::getline(ss, field, ',');
        record.altitude_m = parseValue(field);
    
        std::getline(ss, field, ',');
        record.velocity_mps = parseValue(field);
    
        std::getline(ss, field, ',');
        record.vibration_g = parseValue(field);
    
        std::getline(ss, field, ',');
        record.accel_g = parseValue(field);
    
        data.push_back(record);
    }
    return data;
}