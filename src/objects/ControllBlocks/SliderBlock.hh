#pragma once

#include "../BasicBlock.hh"
#include "Arduino.h"

class SliderBlock: public BasicBlock
{
  public:
    int current_value;
    SliderBlock(int id, int blok_id, const std::vector<int>& pins, const char* name);
    void setValue(int val);
    void resolveInput(String request);
    void update();
    int getValue();
};
