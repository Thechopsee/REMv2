#pragma once
#include "Arduino.h"
#include <functional>
#include "common/DataStruct/GyroAcceleratorDataStruct.hh"

template <typename T>
class Sensor {
public:
  using OnDataChanged = std::function<void(int)>;
  Sensor(std::string name, unsigned long updateInterval);
  std::string name;
  T lastOriginalValue;
  std::string lastValue;
  unsigned long lastUpdate;
  unsigned long updateInterval;

  void SetOnDataChanged(OnDataChanged callback);
  virtual void Begin() = 0;   
  virtual void ReadValue() = 0; 

private:
  OnDataChanged onDataChanged;
};