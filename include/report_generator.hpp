#pragma once

#include <vector>
#include <string>
#include "telemetry_record.hpp"
#include "anomaly_detector.hpp"
#include "fault_detector.hpp"

class ReportGenerator {
public:
    void generate(const std::string& file_path,
                  const std::vector<TelemetryRecord>& data,
                  const std::vector<Anomaly>& anomalies,
                  const std::vector<Fault>& faults);
};