#pragma once

struct Config {
    // Temperature
    double temp_max = 50.0;

    // Pressure
    double pressure_min = 99.0;
    double pressure_max = 102.0;

    // Velocity (trend)
    double velocity_jump = 80.0;

    // Altitude (trend)
    double altitude_jump = 50.0;

    // Vibration
    double vibration_max = 0.3;

    // Acceleration
    double accel_max = 1.2;
};