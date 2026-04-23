#include "telemetry_record.hpp"
#include "csv_reader.hpp"
#include "filter.hpp"
#include "anomaly_detector.hpp"
#include "fault_detector.hpp"
#include "config.hpp"
#include "validator.hpp"
#include "report_generator.hpp"

#include <iostream>

int main() {
    CSVReader reader;
    auto data = reader.read("data/telemetry_data.csv");

    if (data.empty()) {
        std::cerr << "Error: No data loaded.\n";
        return 1;
    }

    // Validation
    Validator validator;
    validator.clean(data);

    // Preserve raw data for anomaly detection
    auto raw_data = data;

    // Filtering (for reporting/smoothing)
    Filter filter;
    filter.applyMovingAverage(data, 3);

    // Anomaly Detection
    Config cfg;
    AnomalyDetector detector(cfg);
    auto anomalies = detector.detect(raw_data);

    // Fault Detection
    FaultDetector faultDetector;
    auto faults = faultDetector.detect(anomalies);

    // Report Generation
    ReportGenerator reporter;
    reporter.generate(
        "output/report.txt",
        data,
        anomalies,
        faults,
        validator
    );

    // Minimal user output
    std::cout << "Analysis complete.\n";
    std::cout << "Report saved to: output/report.txt\n";

    return 0;
}