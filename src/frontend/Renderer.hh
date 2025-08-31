#pragma once

#include "../objects/BasicBlock.hh"
#include <vector>
#include <ESP8266WiFi.h>
#include "../objects/GroupBlock.hh"
#include "../enums/BlockTypeEnum.hh"

class Renderer
{
  public:
    void drawBlock(GroupBlock *bl,WiFiClient client);
    void drawHeader(WiFiClient client);
    void drawOLMJS(WiFiClient client);
    void drawNew(std::vector<GroupBlock *>blocks,WiFiClient client);
  private:
    
    void drawSmallBlock(BasicBlock* cb,WiFiClient client,BlockTypeEnum type);
};
