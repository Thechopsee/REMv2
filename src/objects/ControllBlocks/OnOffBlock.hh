#pragma once

#include "../BasicBlock.hh"
#include "Arduino.h"

class OnOffBlock: public BasicBlock
{
  public:
    int current_value;
    int default_value;
    OnOffBlock(int id, int blok_id, const std::vector<int>& pins, const char* name, int default_value = 0);
    void setPin(bool dat);
    void resolveInput(String request);
    void update();
    void resetToDefault();
    int getValue();
    
};
