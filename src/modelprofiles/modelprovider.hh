#pragma once
#include <vector>
#include <string>
#include "../objects/GroupBlock.hh"
#include "modelprofile.hh"

class ModelProvider
{
private:
    std::vector<GroupBlock*> Groups;
    ModelProfile* modelProfile;
    void freeGroups();
public:
    ModelProvider();
    void LoadModel();
    std::vector<GroupBlock*> GetGroups();
    std::string LoadFromJson(const std::string& json);
};