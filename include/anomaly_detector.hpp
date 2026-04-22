#pragma once

#include <vector>
#include <string>
#include "telemetry_record.hpp"

struct Anomaly{
    long long timestamp;
    std::string sensor;
    std::string type; //"threshold" or "trend"
    double value;
};
//Check if value is outside safe limits → threshold anomaly
//Check if sudden jump from previous → trend anomaly

class AnomalyDetector{
    public:
        std::vector<Anomaly> detect(const std::vector<TelemetryRecord> &data);
};