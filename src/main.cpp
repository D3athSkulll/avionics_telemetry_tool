#include "telemetry_record.hpp"
#include "csv_reader.hpp"
#include "filter.hpp"
#include "anomaly_detector.hpp"

#include <iostream>

int main(){
    CSVReader reader;
    auto data = reader.read("data/telemetry_data.csv");

    std::cout << "Records read: " << data.size() << "\n";

    Filter filter;
    filter.applyMovingAverage(data, 3);
    std::cout << "Applied Filter"<<std::endl;

    AnomalyDetector detector;
    auto anomalies = detector.detect(data);

    std::cout << "\nAnomalies found: " << anomalies.size() << "\n";

    for (int i = 0; i < anomalies.size() && i < 5; i++) {
        std::cout << "Time: " << anomalies[i].timestamp
                  << " Sensor: " << anomalies[i].sensor
                  << " Type: " << anomalies[i].type
                << " Value: " << anomalies[i].value
                << "\n";
    }
    
    return 0;
}