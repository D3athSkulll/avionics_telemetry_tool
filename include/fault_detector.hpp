#pragma once

#include <vector>
#include <string>
#include "anomaly_detector.hpp"

struct Fault {
    long long timestamp;
    std::string description;
};

class FaultDetector {
public:
    std::vector<Fault> detect(const std::vector<Anomaly>& anomalies);
};