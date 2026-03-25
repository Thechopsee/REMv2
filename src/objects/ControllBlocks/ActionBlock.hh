#pragma once 
#include <vector>

#include "../../actions/Action.hh"
#include "../BasicBlock.hh"
#include "Arduino.h"

class ActionBlock: public BasicBlock
{
  private:
     bool isActive;
     Action* action;
  public:
    ActionBlock(int id, int blok_id, const std::vector<int>& pins, const char* name);
    ActionBlock(int id, int blok_id, const std::vector<int>& pins, const char* name, Action* action);
    void setPin(bool dat);
    void resolveInput(String request);
    void update();
    void resetToDefault();
    int getValue();
};
