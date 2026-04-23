#include "report_generator.hpp"

#include <fstream>
#include <iostream>

void ReportGenerator::generate(
    const std::string &file_path,
    const std::vector<TelemetryRecord> &data,
    const std::vector<Anomaly> &anomalies,
    const std::vector<Fault> &faults
){
    std::ofstream out(file_path);

    if (!out.is_open()){
        std::cerr << "Error: Could not create report file\n";
        return;
    }

    // Summary
    out << "=== Telemetry Analysis Report ===\n\n";
    out << "Total records processed: " << data.size() << "\n";
    out << "Total anomalies detected: " << anomalies.size() << "\n";
    out << "Total faults detected: " << faults.size() << "\n\n";

    // Anomalies
    out << "=== Anomalies ===\n";
    for (const auto& a : anomalies) {
        out << "Time: " << a.timestamp
            << ", Sensor: " << a.sensor
            << ", Type: " << a.type
            << ", Value: " << a.value << "\n";
    }

    out <<"\n";

    // Faults
    out << "=== Faults ===\n";
    for (const auto& f : faults) {
        out << "Time: " << f.timestamp
            << " -> " << f.description << "\n";
    }

    out.close();
}
