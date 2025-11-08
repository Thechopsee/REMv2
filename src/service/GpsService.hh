#pragma once
#include <TinyGPSPlus.h>
#include "GpsData.h"

class GpsService {
private:
    HardwareSerial* gpsSerial;
    TinyGPSPlus gps;
    int rxPin, txPin;
    GpsData lastData;

    void handleRoot();

public:
    GpsService(int rx, int tx);
    void begin();
    void update();
    GpsData getData();
};
