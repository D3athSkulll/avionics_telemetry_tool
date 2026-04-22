#pragma once

#include <vector>
#include "telemetry_record.hpp"

class Filter {
public:
    void applyMovingAverage(std::vector<TelemetryRecord>& data, int window_size);
};