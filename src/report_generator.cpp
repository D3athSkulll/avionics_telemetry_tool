#include "report_generator.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include <cmath>

std::string ReportGenerator::generateFilteringAnalysis(
    const std::vector<TelemetryRecord>& raw_data,
    const std::vector<TelemetryRecord>& filtered_data
) {
    std::ostringstream out;

    out << "Moving average filter (window = 3) applied.\n\n";

    double temp_diff = 0, vel_diff = 0;
    int temp_count = 0, vel_count = 0;

    // 🔹 Compute smoothing metrics
    for (size_t i = 0; i < raw_data.size(); i++) {

        if (!std::isnan(raw_data[i].temp_c) &&
            !std::isnan(filtered_data[i].temp_c)) {

            temp_diff += std::abs(raw_data[i].temp_c - filtered_data[i].temp_c);
            temp_count++;
        }

        if (!std::isnan(raw_data[i].velocity_mps) &&
            !std::isnan(filtered_data[i].velocity_mps)) {

            vel_diff += std::abs(raw_data[i].velocity_mps - filtered_data[i].velocity_mps);
            vel_count++;
        }
    }

    double avg_temp = temp_count ? temp_diff / temp_count : 0;
    double avg_vel = vel_count ? vel_diff / vel_count : 0;

    // 🔹 Print quantitative results
    out << "Average smoothing:\n";
    out << "Temperature: " << avg_temp << "\n";
    out << "Velocity: " << avg_vel << "\n\n";

    // 🔹 Sample comparison (dynamic size)
    int sample = std::min((int)raw_data.size(), std::max(3, (int)raw_data.size() / 20));

    out << "Sample comparison (Raw -> Filtered):\n";

    for (int i = 0; i < sample; i++) {
        out << "Time " << raw_data[i].timestamp
            << " | Temp: " << raw_data[i].temp_c
            << " -> " << filtered_data[i].temp_c
            << " | Velocity: " << raw_data[i].velocity_mps
            << " -> " << filtered_data[i].velocity_mps
            << "\n";
    }

    out << "\n";

    // 🔹 Dynamic interpretation
    out << "Interpretation:\n";

    // Temperature analysis
    if (avg_temp < 0.1)
        out << "- Temperature signal is highly stable (minimal smoothing needed).\n";
    else if (avg_temp < 1.0)
        out << "- Moderate temperature smoothing observed.\n";
    else
        out << "- High temperature fluctuations detected (filter significantly reduced noise).\n";

    // Velocity analysis
    if (avg_vel < 1.0)
        out << "- Velocity signal is stable.\n";
    else if (avg_vel < 10.0)
        out << "- Moderate velocity variations smoothed.\n";
    else
        out << "- Significant velocity spikes present (high smoothing impact).\n";

    out << "\n";

    return out.str();
}

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
    const std::vector<TelemetryRecord> &filtered_data,
    const std::vector<TelemetryRecord> &cleaned_data,
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
    out << "=== Validated Data Telemetry Analysis Report ===\n\n";
    out << "Total records processed: " << cleaned_data.size() << "\n";
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

    out << "=== Cleaned Data Analysis Summary ===\n";
    out << generateAnalysis(anomalies, faults);


    out << "=== Filtering Effect & Analysis ===\n";
    out << generateFilteringAnalysis(cleaned_data, filtered_data);
    out.close();
}
