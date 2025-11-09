#pragma once
#include <U8g2lib.h>
#include "DisplayBridge.hh"
#include <Arduino.h>
#include <string>

class ZeroFortyTwo : public DisplayBridge
{
public:
    U8G2_SSD1306_96X40_F_HW_I2C u8g2;
    ZeroFortyTwo(int width, int height);

    void clear() override;
    void write(std::string text) override;
    void drawBitmap(const unsigned char* bitmap) override;
};