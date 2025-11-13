#pragma once
#include <Wire.h>
#include <MPU6050.h>
#include "Sensor.hh"
#include "../common/DataStruct/GyroAcceleratorDataStruct.hh"

class MPU6050Sensor : public Sensor<GyroAcceleratorDataStruct> {
public:
  MPU6050Sensor(std::string name, unsigned long updateInterval, int sdaPin = 21, int sclPin = 22);
  void Begin() override;
  void ReadValue() override;

private:
  int _sdaPin;
  int _sclPin;
  MPU6050 _mpu;
  bool _initialized = false;
};
