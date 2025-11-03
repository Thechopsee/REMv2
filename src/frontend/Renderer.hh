#pragma once

#include <vector>
#include <Print.h> 

#include "../objects/BasicBlock.hh"
#include "../objects/GroupBlock.hh"
#include "../enums/BlockTypeEnum.hh"

class Renderer
{
  public:
    void drawBlock(GroupBlock *bl,Print &client);
    void drawHeader(Print &client);
    void drawOLMJS(Print &client);
    void drawNew(std::vector<GroupBlock *>blocks,Print &client);
  private:
    
    void drawSmallBlock(BasicBlock* cb,Print &client,BlockTypeEnum type);
};
