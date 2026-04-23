#include "report_generator.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

std::string ReportGenerator::generateAnalysis(
    const std::vector<Anomaly> &anomalies,
    const std::vector<Fault> &faults
) {
    int temp = 0, pressure = 0, velocity = 0;
    int vibration = 0, accel = 0, altitude = 0;

    for (const auto& a : anomalies) {
        if (a.sensor == "temp_c") temp++;
        else if (a.sensor == "pressure_kpa") pressure++;
        else if (a.sensor == "velocity_mps") velocity++;
        else if (a.sensor == "vibration_g") vibration++;
        else if (a.sensor == "accel_g") accel++;
        else if (a.sensor == "altitude_m") altitude++;
    }

    std::string dominant = "none";
    int max_count = 0;

    if (temp > max_count) { max_count = temp; dominant = "temperature"; }
    if (pressure > max_count) { max_count = pressure; dominant = "pressure"; }
    if (velocity > max_count) { max_count = velocity; dominant = "velocity"; }
    if (vibration > max_count) { max_count = vibration; dominant = "vibration"; }
    if (accel > max_count) { max_count = accel; dominant = "acceleration"; }
    if (altitude > max_count) { max_count = altitude; dominant = "altitude"; }

    std::ostringstream out;


    if (anomalies.empty()) {
        out << "No anomalies were detected in the dataset.\n";
    } else {
        out << "Total anomalies detected: " << anomalies.size() << ".\n";
        out << "Most anomalies occurred in " << dominant
            << " (" << max_count << " occurrences).\n";

        if (velocity > 0)
            out << "Velocity spikes indicate abrupt system changes.\n";

        if (temp > 0)
            out << "Temperature spikes suggest thermal variations.\n";

        if (vibration > 0 || accel > 0)
            out << "Vibration/acceleration anomalies indicate possible mechanical stress.\n";

        if (pressure > 0)
            out << "Pressure deviations indicate environmental inconsistencies.\n";
    }

    if (faults.empty()) {
        out << "No critical faults were detected.\n";
    } else {
        out << "Faults were triggered due to combined anomalies.\n";
    }

    out << "\n";

    return out.str();
}

void ReportGenerator::generate(
    const std::string &file_path,
    const std::vector<TelemetryRecord> &data,
    const std::vector<Anomaly> &anomalies,
    const std::vector<Fault> &faults,
    const Validator &validator
){
    std::ofstream out(file_path);

    if (!out.is_open()){
        std::cerr << "Error: Could not create report file\n";
        return;
    }

    // Data Quality
    out << "=== Raw Data Quality ===\n";
    out << "Original records: " << validator.original_size << "\n";
    out << "Final records: " << validator.final_size << "\n";
    out << "Duplicates removed: " << validator.duplicates_removed << "\n\n";
    
    // Summary
    out << "=== Cleaned Data Telemetry Analysis Report ===\n\n";
    out << "Total records processed: " << data.size() << "\n";
    out << "Total anomalies detected: " << anomalies.size() << "\n";
    out << "Total faults detected: " << faults.size() << "\n\n";

    int temp_count = 0, pressure_count = 0, velocity_count = 0;
    int vibration_count = 0, accel_count = 0, altitude_count = 0;

    for (const auto& a : anomalies) {
        if (a.sensor == "temp_c") temp_count++;
        else if (a.sensor == "pressure_kpa") pressure_count++;
        else if (a.sensor == "velocity_mps") velocity_count++;
        else if (a.sensor == "vibration_g") vibration_count++;
        else if (a.sensor == "accel_g") accel_count++;
        else if (a.sensor == "altitude_m") altitude_count++;
    }

    out << "=== Anomaly Breakdown ===\n";
    out << "Temperature anomalies: " << temp_count << "\n";
    out << "Pressure anomalies: " << pressure_count << "\n";
    out << "Velocity anomalies: " << velocity_count << "\n";
    out << "Vibration anomalies: " << vibration_count << "\n";
    out << "Acceleration anomalies: " << accel_count << "\n";
    out << "Altitude anomalies: " << altitude_count << "\n\n";

    // Anomalies
    out << "=== Anomalies ===\n";
    if(anomalies.size()>0){
        for (const auto& a : anomalies) {
            out << "Time: " << a.timestamp
                << ", Sensor: " << a.sensor
                << ", Type: " << a.type
                << ", Value: " << a.value << "\n";
        }
    }else{
        out<<"None\n";
    }

    out <<"\n";

    // Faults
    out << "=== Faults ===\n";
    if(faults.size()>0){
        for (const auto& f : faults) {
            out << "Time: " << f.timestamp
                << " -> " << f.description << "\n";
        }
    }else{
        out<< "None\n";
    }
    
    out <<"\n";

    out << "=== Analysis Summary ===\n";
    out << generateAnalysis(anomalies, faults);

    out.close();
}
