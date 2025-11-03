#pragma once

#include "DisplayBridge.hh"
#include "DisplayBridgeFactory.hh"
#include "../enums/DisplayTypeEnum.hh"

class UniversalDisplay
{
    private:
    DisplayBridge* bridge;
    public:
    UniversalDisplay(DisplayTypeEnum display);
};
