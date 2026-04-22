#pragma once

#include <cstdint>

struct TelemetryRecord{
    std::int64_t timestamp{};

    double temp_c{};
    double pressure_kpa{};
    double altitude_m{};
    double velocity_mps{};
    double vibration_g{};
    double accel_g{};

    bool valid{true};
};