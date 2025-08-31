#pragma once ¨

#include <vector>
#include <string>
#include "Arduino.h"

class BasicBlock 
{
  public:
    int id;
    int blok_id;
    std::vector<int> pins;
    char* name;
    std::string actual_status;

    BasicBlock(int id, int blok_id, const std::vector<int>& pins, char* name);
    virtual void setPin(bool dat);
    virtual void update();
    virtual void resolveInput(String request);
};
