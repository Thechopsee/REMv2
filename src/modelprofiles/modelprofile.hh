#pragma once
#include <vector>
#include "../objects/GroupBlock.hh"

class ModelProfile{
public:
    virtual std::vector<GroupBlock*> LoadModel() = 0;
};
