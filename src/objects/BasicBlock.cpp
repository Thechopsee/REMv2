#include "BasicBlock.hh"

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

void BasicBlock::resolveInput(String request)
{
  return;
}

