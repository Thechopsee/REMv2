#pragma once

#include "../BasicBlock.hh"
#include "Arduino.h"

class SliderBlock: public BasicBlock
{
  public:
    int current_value;
    int defaultValue;
    SliderBlock(int id, int blok_id, const std::vector<int>& pins, const char* name, int defaultValue = 0);
    void setValue(int val);
    void resolveInput(String request);
    void update();
    int getValue();
    void resetToDefault() override;
};
