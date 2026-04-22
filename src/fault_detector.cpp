#include "fault_detector.hpp"

std::vector<Fault> FaultDetector::detect(const std::vector<Anomaly> &anomalies){

    std::vector<Fault> faults;

    for(size_t i = 0; i < anomalies.size(); i++){
        
        const auto &a = anomalies[i];

        //Rule 1 : High Vibration + high Accel
        if(a.sensor == "vibration_g"){
            for (size_t j = 0; i < anomalies.size(); j++){
                if(anomalies[j].timestamp == a.timestamp &&
                    anomalies[j].sensor == "accel_g"){
                        faults.push_back({
                            a.timestamp,
                            "Mechanical instability detected"
                        });
                    }
            }
            
        }

        //Rule 2 : Altitude trend anomaly
        if(a.sensor == "altitude_m" && a.type == "trend"){
            faults.push_back({
                a.timestamp,
                "Altitude instability detected"
            });
        }

        //Rule 3: Multiple anomalies at same timestamp
        int count = 0;
        for(const auto &b : anomalies){
            if (b.timestamp == a.timestamp){
                count++;
            }
        }

        if(count>=3){
            faults.push_back({
                a.timestamp,
                "Multiple sensor anomalies detected"
            });
        }
    }
    return faults;
}