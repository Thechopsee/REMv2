#pragma once

#include "DisplayBridge.hh"
#include "DisplayBridgeFactory.hh"
#include <U8g2lib.h>
#include "../enums/DisplayTypeEnum.hh"


class UniversalDisplay
{
    private:
    DisplayBridge* bridge;
    public:
    UniversalDisplay(DisplayTypeEnum display, int sda, int scl, int reset = U8X8_PIN_NONE);
    void drawBitmap(const unsigned char* bitmap);
    void write(std::string text);
    void clear();
};
