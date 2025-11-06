#pragma once
#include "Arduino.h"

class Sensor {
public:
  Sensor(std::string name, unsigned long updateInterval);
  std::string name;
  std::string lastValue;
  unsigned long lastUpdate;
  unsigned long updateInterval;
  virtual void Begin() = 0;   
  virtual void ReadValue() = 0; 
};