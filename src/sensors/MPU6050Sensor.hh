#pragma once
#include <Wire.h>
#include <MPU6050_light.h>
#include "Sensor.h"

class MPU6050Sensor : public Sensor {
public:
  MPU6050Sensor(String name, unsigned long updateInterval, int sdaPin, int sclPin);

  void Begin() override;
  void ReadValue() override;

private:
  int _sdaPin;
  int _sclPin;
  TwoWire _wire;
  MPU6050 _mpu;
};
