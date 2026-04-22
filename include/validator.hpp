#pragma once

#include <vector>
#include "telemetry_record.hpp"

class Validator {
public:
    void clean(std::vector<TelemetryRecord>& data);
};