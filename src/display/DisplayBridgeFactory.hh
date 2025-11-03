#pragma once

#include "DisplayBridge.hh"
#include "../enums/DisplayTypeEnum.hh"

class DisplayBridgeFactory
{
    public:
    static DisplayBridge* create(DisplayTypeEnum type);
};