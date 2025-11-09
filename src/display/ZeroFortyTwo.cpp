#include "ZeroFortyTwo.hh"

ZeroFortyTwo::ZeroFortyTwo(int width, int height)
: u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE)
{
    u8g2.begin();
    this->widthInPixels=width;
    this->heightInPixels=height;
}

void ZeroFortyTwo::clear()
{
    u8g2.clearBuffer();
}

void ZeroFortyTwo::write(std::string text)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(30, 2, text.c_str());
  u8g2.drawFrame(30, 0, 72, 40);
  u8g2.sendBuffer();
}

void ZeroFortyTwo::drawBitmap(const unsigned char* bitmap)
{
  u8g2.clearBuffer();
  u8g2.drawXBMP(30, 20, 72, 40, bitmap);
  u8g2.sendBuffer();

}
