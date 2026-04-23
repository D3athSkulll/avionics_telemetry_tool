#pragma once

#include <vector>
#include <string>
#include "telemetry_record.hpp"
#include "anomaly_detector.hpp"
#include "fault_detector.hpp"
#include "validator.hpp"

class ReportGenerator {
    public:
        void generate(
            const std::string& file_path,
            const std::vector<TelemetryRecord>& data,
            const std::vector<TelemetryRecord>& cleaned_data,
            const std::vector<Anomaly>& anomalies,
            const std::vector<Fault>& faults,
            const Validator &validator
        );

    private:
        std::string generateAnalysis(
            const std::vector<Anomaly> &anomalies,
            const std::vector<Fault> &faults
        );
        std::string generateFilteringAnalysis(
            const std::vector<TelemetryRecord>& cleaned_data,
            const std::vector<TelemetryRecord>& filtered_data
        );
};