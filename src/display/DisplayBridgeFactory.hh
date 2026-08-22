#pragma once

#include "DisplayBridge.hh"
#include <U8g2lib.h>
#include "../enums/DisplayTypeEnum.hh"

class DisplayBridgeFactory
{
    public:
    static DisplayBridge* create(DisplayTypeEnum type, int sda, int scl, int reset = U8X8_PIN_NONE);
};