#include "filter.hpp"

//Apply moving average to each sensor field
void Filter::applyMovingAverage(std::vector<TelemetryRecord> &data, int window_size){
 
    if (data.empty() || window_size <= 1) return;

    std::vector<TelemetryRecord> smoothed = data;

    for (size_t i = 0; i< data.size(); i++){
        int count = 0;

        double temp_sum = 0;
        double pressure_sum = 0;
        double altitude_sum = 0;
        double velocity_sum = 0;
        double vibration_sum = 0;
        double accel_sum = 0;

        //window loop
        for (int j = (int)i - window_size + 1; j <= (int) i; j++)
        {
            if (j >= 0)
            {
                temp_sum = temp_sum + data[j].temp_c;
                pressure_sum = pressure_sum + data[j].pressure_kpa;
                velocity_sum = velocity_sum + data[j].velocity_mps;
                vibration_sum = vibration_sum + data[j].vibration_g;
                accel_sum = accel_sum + data[j].accel_g;
                count++;
            }
            
        }
        
        //assigning averages
        smoothed[i].temp_c = temp_sum / count;
        smoothed[i].pressure_kpa = pressure_sum / count;
        smoothed[i].altitude_m = altitude_sum / count;
        smoothed[i].velocity_mps = velocity_sum / count;
        smoothed[i].vibration_g = vibration_sum / count;
        smoothed[i].accel_g = accel_sum / count;
    }

    data = smoothed;
}