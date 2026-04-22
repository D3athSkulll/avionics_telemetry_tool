#pragma once

#include "validator.hpp"
#include <algorithm>

void Validator::clean(std::vector<TelemetryRecord>& data){
    
    //Remove Invalid Records
    std::vector<TelemetryRecord> valid_data;

    for( const auto &record : data){
        if (record.valid){
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
        }

        data = unique_data;
    }
}