#include "GpsService.h"

GpsService::GpsService(int rx, int tx)
    : gpsSerial(&Serial1), rxPin(rx), txPin(tx) {}

void GpsService::begin() {
    gpsSerial->begin(9600, SERIAL_8N1, rxPin, txPin);
    server.on("/", [this]() { handleRoot(); });
    server.begin();
}

void GpsService::update() {
    while (gpsSerial->available() > 0) {
        if (gps.encode(gpsSerial->read())) {
            if (gps.location.isValid()) {
                lastData.lat = gps.location.lat();
                lastData.lng = gps.location.lng();
            }
            if (gps.altitude.isValid()) {
                lastData.alt = gps.altitude.meters();
            }
            if (gps.speed.isValid()) {
                lastData.speed = gps.speed.kmph();
            }
            if (gps.time.isValid()) {
                char buf[16];
                sprintf(buf, "%02d:%02d:%02d",
                        gps.time.hour(), gps.time.minute(), gps.time.second());
                lastData.time = String(buf);
            }
        }
    }

    server.handleClient();
}

GpsData GpsService::getData() {
    return lastData;
}

