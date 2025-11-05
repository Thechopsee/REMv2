#pragma once

#include "../BasicBlock.hh"
#include "../../sensors/Sensor.hh"
#include "Arduino.h"

class TextSensorBlock: public BasicBlock
{
  public:
    String current_value;
    Sensor* sensor;
    TextSensorBlock(int id, int blok_id, const std::vector<int>& pins, const char* name,Sensor* sensor);
    void setPin(bool dat);
    void resolveInput(String request);
    void update();
    String getValue();
    
};
