#include "AdafruitSSD1306.hh"

AdafruitSSD1306::AdafruitSSD1306(int width, int height, int sda, int scl, int reset)
: u8g2(U8G2_R0, reset, scl, sda)
{
    u8g2.begin();
    this->widthInPixels = width;
    this->heightInPixels = height;
}

void AdafruitSSD1306::clear()
{
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}

void AdafruitSSD1306::write(std::string text)
{
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(0, 10, text.c_str());
    u8g2.drawFrame(0, 0, widthInPixels, heightInPixels);
    u8g2.sendBuffer();
}

void AdafruitSSD1306::drawBitmap(const unsigned char* bitmap)
{
    u8g2.clearBuffer();
    u8g2.drawXBMP(0, 0, widthInPixels, heightInPixels, bitmap);
    u8g2.sendBuffer();
}
