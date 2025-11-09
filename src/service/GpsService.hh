#pragma once
#include <TinyGPSPlus.h>
#include "GpsData.hh"

class GpsService {
private:
    HardwareSerial* gpsSerial;
    TinyGPSPlus gps;
    int rxPin, txPin;
    GpsData lastData;

public:
    GpsService(int rx, int tx);
    void begin();
    void update();
    GpsData getData();
};
