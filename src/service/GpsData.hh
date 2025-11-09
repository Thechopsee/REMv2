#pragma once
#include <Arduino.h>

struct GpsData {
    double lat = 0.0;
    double lng = 0.0;
    double alt = 0.0;
    double speed = 0.0;
    String time = "N/A";
};
