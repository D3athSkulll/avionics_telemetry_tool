#include <iostream>
#include <vector>
#include <cmath>

#include "telemetry_record.hpp"
#include "validator.hpp"
#include "filter.hpp"
#include "anomaly_detector.hpp"
#include "fault_detector.hpp"
#include "config.hpp"

// ---------------- VALIDATOR TEST ----------------
void testValidator() {
    std::vector<TelemetryRecord> data = {
        {2, 25, 101, 1000, 250, 0.02, 1.0},
        {1, 25, 101, 1000, 250, 0.02, 1.0},
        {1, 25, 101, 1000, 250, 0.02, 1.0}
    };

    Validator v;
    v.clean(data);

    if (data.size() == 2 && data[0].timestamp == 1) {
        std::cout << "Validator Test Passed\n";
    } else {
        std::cout << "Validator Test Failed\n";
    }
}

// ---------------- FILTER TEST ----------------
void testFilter() {
    std::vector<TelemetryRecord> data = {
        {0, 25, 101, 1000, 200, 0.02, 1.0},
        {1, 27, 101, 1000, 300, 0.02, 1.0},
        {2, 29, 101, 1000, 400, 0.02, 1.0}
    };

    Filter f;
    f.applyMovingAverage(data, 3);

    if (data[2].temp_c < 29 && data[2].temp_c > 25) {
        std::cout << "Filter Test Passed\n";
    } else {
        std::cout << "Filter Test Failed\n";
    }
}

// ---------------- ANOMALY TEST ----------------
void testAnomaly() {
    std::vector<TelemetryRecord> data = {
        {0, 25, 101, 1000, 250, 0.02, 1.0},
        {1, 25, 101, 1000, 450, 0.02, 1.0} // spike
    };

    Config cfg;
    AnomalyDetector detector(cfg);
    auto anomalies = detector.detect(data);

    if (!anomalies.empty()) {
        std::cout << "Anomaly Test Passed\n";
    } else {
        std::cout << "Anomaly Test Failed\n";
    }
}

// ---------------- FAULT TEST ----------------
void testFault() {
    std::vector<Anomaly> anomalies = {
        {1, "vibration_g", "threshold", 3.0},
        {1, "accel_g", "threshold", 6.0}
    };

    FaultDetector fd;
    auto faults = fd.detect(anomalies);

    if (!faults.empty()) {
        std::cout << "Fault Test Passed\n";
    } else {
        std::cout << "Fault Test Failed\n";
    }
}

// ---------------- EDGE CASE TEST ----------------
void testEdgeCase() {
    std::vector<TelemetryRecord> data; // empty

    Config cfg;
    AnomalyDetector detector(cfg);
    auto anomalies = detector.detect(data);

    if (anomalies.empty()) {
        std::cout << "Edge Case Test Passed\n";
    } else {
        std::cout << "Edge Case Test Failed\n";
    }
}

// ---------------- MAIN ----------------
int main() {
    testValidator();
    testFilter();
    testAnomaly();
    testFault();
    testEdgeCase();
    return 0;
}