#pragma once

#include "telemetry_record.hpp"
#include "config.hpp"

#include <vector>
#include <string>
struct Anomaly{
    long long timestamp;
    std::string sensor;
    std::string type; //"threshold" or "trend"
    double value;
};
//Check if value is outside safe limits → threshold anomaly
//Check if sudden jump from previous → trend anomaly

class AnomalyDetector{
    private:
        Config config;
    public:
        AnomalyDetector(const Config& c = Config()) : config(c) {}

        std::vector<Anomaly> detect(const std::vector<TelemetryRecord> &data);
};