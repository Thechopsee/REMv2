#pragma once

#include "../BasicBlock.hh"
#include "Arduino.h"

class OnOffBlock: public BasicBlock
{
  public:
    int current_value;
    OnOffBlock(int id, int blok_id, const std::vector<int>& pins, const char* name);
    void setPin(bool dat);
    void resolveInput(String request);
    void update();
    int getValue();
    
};
