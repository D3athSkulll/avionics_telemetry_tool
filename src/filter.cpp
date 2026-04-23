#include "filter.hpp"
#include <cmath>

//Apply moving average to each sensor field
void Filter::applyMovingAverage(std::vector<TelemetryRecord> &data, int window_size){
 
    if (data.empty() || window_size <= 1) return;

    std::vector<TelemetryRecord> smoothed = data;

    for (size_t i = 0; i< data.size(); i++){
        int temp_count = 0;
        int pressure_count = 0;
        int altitude_count = 0;
        int velocity_count = 0;
        int vibration_count = 0;
        int accel_count = 0;

        double temp_sum = 0;
        double pressure_sum = 0;
        double altitude_sum = 0;
        double velocity_sum = 0;
        double vibration_sum = 0;
        double accel_sum = 0;

        //window loop
        for (int j = (int)i - window_size + 1; j <= (int) i; j++)
        {
            if (j >= 0){
                if (!std::isnan(data[j].temp_c)) {
                    temp_sum += data[j].temp_c;
                    temp_count++;
                }

                if (!std::isnan(data[j].pressure_kpa)) {
                    pressure_sum += data[j].pressure_kpa;
                    pressure_count++;
                }

                if (!std::isnan(data[j].altitude_m)) {
                    altitude_sum += data[j].altitude_m;
                    altitude_count++;
                }

                if (!std::isnan(data[j].velocity_mps)) {
                    velocity_sum += data[j].velocity_mps;
                    velocity_count++;
                }

                if (!std::isnan(data[j].vibration_g)) {
                    vibration_sum += data[j].vibration_g;
                    vibration_count++;
                }

                if (!std::isnan(data[j].accel_g)) {
                    accel_sum += data[j].accel_g;
                    accel_count++;
                }
            }
        }
            
        
        //assigning averages
        smoothed[i].temp_c = temp_count ? temp_sum / temp_count : data[i].temp_c;
        smoothed[i].pressure_kpa = pressure_count ? pressure_sum / pressure_count : data[i].pressure_kpa;
        smoothed[i].altitude_m = altitude_count ? altitude_sum / altitude_count : data[i].altitude_m;
        smoothed[i].velocity_mps = velocity_count ? velocity_sum / velocity_count : data[i].velocity_mps;
        smoothed[i].vibration_g = vibration_count ? vibration_sum / vibration_count : data[i].vibration_g;
        smoothed[i].accel_g = accel_count ? accel_sum / accel_count : data[i].accel_g;

    }
    data = smoothed;

}