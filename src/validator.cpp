#include "validator.hpp"
#include <algorithm>

void Validator::clean(std::vector<TelemetryRecord>& data){

     original_size = data.size();
    
    //Remove Invalid Records
    std::vector<TelemetryRecord> valid_data;

    for( const auto &record : data){
        if (record.timestamp >= 0){
            valid_data.push_back(record);
        }
    }

    data = valid_data;

    // Sort by timestamp
    std::sort(data.begin(), data.end(),
        [](const TelemetryRecord &a, const TelemetryRecord &b){
            return a.timestamp < b.timestamp;
        }
    );

    // Remove Duplicate Timestamps
    std::vector<TelemetryRecord> unique_data;

    for( size_t i = 0; i < data.size(); i++){
        if (i == 0 || data[i].timestamp != data[i-1].timestamp){
            unique_data.push_back(data[i]);
        } else{
            duplicates_removed++;
        }
    }
    data = unique_data;
    final_size = data.size();
}