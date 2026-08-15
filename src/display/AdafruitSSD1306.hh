#pragma once
#include <U8g2lib.h>
#include "DisplayBridge.hh"
#include <Arduino.h>
#include <string>

class AdafruitSSD1306 : public DisplayBridge
{
public:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
    AdafruitSSD1306(int width, int height);

    void clear() override;
    void write(std::string text) override;
    void drawBitmap(const unsigned char* bitmap) override;
};
