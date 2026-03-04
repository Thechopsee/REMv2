#include "BasicBlock.hh"

#include <algorithm>

BasicBlock::BasicBlock(int id, int blok_id, const std::vector<int>& pins, const char* name)
{
    this->id=id;
    this->blok_id=blok_id;
    this->pins=pins;
    this->name=name;
    this->enabled=true;
}

void BasicBlock::setPin(bool dat)
{
  return;
}

void BasicBlock::resetToDefault()
{
  return;
}

bool BasicBlock::sharesPinsWith(BasicBlock* other)
{
    if (this == other) return false;
    for (int p1 : this->pins) {
        for (int p2 : other->pins) {
            if (p1 == p2) return true;
        }
    }
    return false;
}

bool BasicBlock::isRunningAction()
{
    return false;
}

void BasicBlock::resolveInput(String request)
{
  return;
}

