#include "MPU6050Sensor.h"

MPU6050Sensor::MPU6050Sensor(String name, unsigned long updateInterval, int sdaPin, int sclPin)
  : Sensor(name, updateInterval),
    _sdaPin(sdaPin),
    _sclPin(sclPin),
    _wire(0),
    _mpu(_wire)
{}

void MPU6050Sensor::Begin() {
  _wire.begin(_sdaPin, _sclPin);
  byte status = _mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  _mpu.calcOffsets(true,true);
}

void MPU6050Sensor::ReadValue() {
  if (millis() - lastUpdate >= updateInterval) 
  {
    _mpu.update();
    char buf[128];
    sprintf(buf, "AX: %.2f, AY: %.2f, AZ: %.2f, GX: %.2f, GY: %.2f, GZ: %.2f, ANGX: %.2f, ANGY: %.2f, ANGZ: %.2f, TEMP: %.2f", 
            mpu.getAccX(), mpu.getAccY(), mpu.getAccZ(), 
            mpu.getGyroX(), mpu.getGyroY(), mpu.getGyroZ(),
            mpu.getAngleX(), mpu.getAngleY(), mpu.getAngleZ(), 
            mpu.getTemp());

    lastValue = String(buf);
    lastUpdate = millis();
  }
}
