#pragma once

#include "../BasicBlock.hh"
#include "Arduino.h"

class InputSliderBlock: public BasicBlock
{
  public:
    int current_value;
    int max_value;
    InputSliderBlock(int id, int blok_id, const std::vector<int>& pins, const char* name, int max_val = 180, int default_value = 0);
    void setValue(int val);
    void resolveInput(String request);
    void update();
    int getValue();
};
