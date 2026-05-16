#pragma once
#include <vector>
#include <string>
#include "../objects/GroupBlock.hh"

class ProfilePrettyPrinter {
public:
    static std::string serialize(const std::vector<GroupBlock*>& groups);
};
