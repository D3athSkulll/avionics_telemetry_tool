#include "anomaly_detector.hpp"

#include <cmath>

std::vector<Anomaly> AnomalyDetector::detect(const std::vector<TelemetryRecord>& data){

    std::vector<Anomaly> anomalies;
    
    if (data.empty()) return anomalies;

    double last_valid_velocity = 0;
    bool has_valid_velocity = false;

    double last_valid_altitude = 0;
    bool has_valid_altitude = false;


    for (size_t i = 0; i < data.size(); i++){
        const auto &curr = data[i];

        if (std::isnan(curr.temp_c) ||
            std::isnan(curr.pressure_kpa) ||
            std::isnan(curr.altitude_m) ||
            std::isnan(curr.velocity_mps) ||
            std::isnan(curr.vibration_g) ||
            std::isnan(curr.accel_g)) {
            continue;  // skip invalid record
        }

        //Threshold based checks
        if (curr.temp_c < -40 || curr.temp_c > config.temp_max){
            anomalies.push_back({
                curr.timestamp,
                "temp_c",
                "threshold",
                curr.temp_c,
            });
        }

        if (curr.pressure_kpa < config.pressure_min || curr.pressure_kpa > config.pressure_max){
            anomalies.push_back({
                curr.timestamp,
                "pressure_kpa",
                "threshold",
                curr.pressure_kpa,
            });
        }

        if (curr.vibration_g > config.vibration_max){
            anomalies.push_back({
                curr.timestamp,
                "vibration_g",
                "threshold",
                curr.vibration_g,
            });
        }

        if (curr.accel_g > config.accel_max){
            anomalies.push_back({
                curr.timestamp,
                "accel_g",
                "threshold",
                curr.accel_g,
            });
        }

        // Trend-based checks

        // --- Altitude trend ---
        if (!has_valid_altitude) {
            last_valid_altitude = curr.altitude_m;
            has_valid_altitude = true;
        } else {
            if (std::abs(curr.altitude_m - last_valid_altitude) > config.altitude_jump) {
                anomalies.push_back({
                    curr.timestamp,
                    "altitude_m",
                    "trend",
                    curr.altitude_m,
                });
            }
            last_valid_altitude = curr.altitude_m;
        }

        // --- Velocity trend ---
        // Initialize first valid velocity
        if (!has_valid_velocity) {
            last_valid_velocity = curr.velocity_mps;
            has_valid_velocity = true;
        } else{
            double prev_velocity = last_valid_velocity;
            // Detect Spikes in velocity
            if (curr.velocity_mps > prev_velocity + config.velocity_jump) {
                anomalies.push_back({
                    curr.timestamp,
                    "velocity_mps",
                    "trend",
                    curr.velocity_mps,
                });
                // cooldown = 2;  // activate cooldown
            }
            last_valid_velocity = curr.velocity_mps;
        }
    }
    return anomalies;    
}