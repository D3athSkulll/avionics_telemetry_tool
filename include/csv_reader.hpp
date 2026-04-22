#pragma once

#include <string>
#include <vector>
#include "telemetry_record.hpp"

class CSVReader {
public:
    std::vector<TelemetryRecord> read(const std::string& file_path);
};