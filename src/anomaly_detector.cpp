#include "anomaly_detector.hpp"

#include <cmath>

std::vector<Anomaly> AnomalyDetector::detect(const std::vector<TelemetryRecord>& data){

    std::vector<Anomaly> anomalies;

    for (size_t i = 0; i < data.size(); i++)
    {
        const auto &curr = data[i];

        //Threshold based checks
        if (curr.temp_c < 40 || curr.temp_c > 85){
            anomalies.push_back({
                curr.timestamp,
                "temp_c",
                "threshold",
                curr.temp_c,
            });
        }

        if (curr.vibration_g > 2.0){
            anomalies.push_back({
                curr.timestamp,
                "vibration_g",
                "threshold",
                curr.vibration_g,
            });
        }

        if (curr.accel_g > 5.0){
            anomalies.push_back({
                curr.timestamp,
                "accel_g",
                "threshold",
                curr.accel_g,
            });
        }

        if (i>0){
            const auto &prev = data[i-1];

            if (std::abs(curr.altitude_m - prev.altitude_m) > 100){
                anomalies.push_back({
                    curr.timestamp,
                    "altitude_m",
                    "trend",
                    curr.altitude_m,
                });
            }

            if (std::abs(curr.velocity_mps - prev.velocity_mps) > 50){
                anomalies.push_back({
                    curr.timestamp,
                    "velocity_mps",
                    "trend",
                    curr.velocity_mps,
                });
            }
        }
    }
    return anomalies;    
}