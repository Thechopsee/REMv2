#pragma once
#include <vector>
#include <string>

#include "../objects/BasicBlock.hh"
#include "../enums/BlockTypeEnum.hh"

class GroupBlock {       
  public:            
    BlockTypeEnum type;
    int id;
    std::vector<BasicBlock*> blocks;
    GroupBlock(int id,BlockTypeEnum type);     
};