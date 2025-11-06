#pragma once

#include <vector>
#include <string>
#include "Arduino.h"

class BasicBlock 
{
  public:
    int id;
    int blok_id;
    std::vector<int> pins;
    const char* name;
    std::string actual_status;

    BasicBlock(int id, int blok_id, const std::vector<int>& pins, const char* name);
    virtual void setPin(bool dat);
    virtual void update() = 0;
    virtual void resolveInput(String request);
};
