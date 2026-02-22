#pragma once
#include "Arduino.h"
#include <functional>
#include "common/DataStruct/GyroAcceleratorDataStruct.hh"
#include "../service/StorageService.hh"

template <typename T>
class Sensor {
public:
  using OnDataChanged = std::function<void(int)>;
  Sensor(std::string name, unsigned long updateInterval, bool enableLogging = false);
  std::string name;
  T lastOriginalValue;
  std::string lastValue;
  unsigned long lastUpdate;
  unsigned long updateInterval;
  bool loggingEnabled;

  void SetOnDataChanged(OnDataChanged callback);
  virtual void Begin() = 0;   
  void ReadValue(); 

protected:
  virtual void ReadValueInternal() = 0; 
  void LogSensorData(const std::string& data); 

private:
  OnDataChanged onDataChanged;
};