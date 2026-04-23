#pragma once

#include <vector>
#include "telemetry_record.hpp"

class Validator {
public:
    int duplicates_removed = 0;
    int original_size = 0;
    int final_size = 0;
    
    void clean(std::vector<TelemetryRecord>& data);
};