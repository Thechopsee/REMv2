#pragma once
#include <vector>
#include "../objects/GroupBlock.hh"
#include "modelprofile.hh"

class ModelProvider
{
private:
    std::vector<GroupBlock*> Groups;
    ModelProfile* modelProfile;
public:
    ModelProvider();
    void LoadModel();
    std::vector<GroupBlock*> GetGroups();
};