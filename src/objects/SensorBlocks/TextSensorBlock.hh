#pragma once

#include "../BasicBlock.hh"
#include "../../sensors/Sensor.hh"
#include "Arduino.h"

template <typename T>
class TextSensorBlock: public BasicBlock
{
  public:
    std::string current_value;
    Sensor<T>* sensor;
    TextSensorBlock(int id, int blok_id, const std::vector<int>& pins, const char* name,Sensor<T>* sensor);
    void setPin(bool dat);
    void resolveInput(String request);
    void update() override;
    std::string getValue();
    
};
