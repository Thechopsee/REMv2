#include "AdafruitSSD1306_64x32.hh"

AdafruitSSD1306_64x32::AdafruitSSD1306_64x32(int width, int height, int sda, int scl, int reset)
: u8g2(U8G2_R0, reset, scl, sda)
{
    u8g2.begin();
    this->widthInPixels = width;
    this->heightInPixels = height;
}

void AdafruitSSD1306_64x32::clear()
{
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}

void AdafruitSSD1306_64x32::write(std::string text)
{
    u8g2.clearBuffer();

    // Fonts in size order (largest -> smallest). We pick the first one whose
    // rendered width fits inside the display frame, so long text (e.g. the IP
    // address "192.168.1.100") no longer gets cut off on the 64px wide OLED.
    const uint8_t* fonts[] = {
        u8g2_font_6x10_tf,       // for short words like "REMv2"
        u8g2_font_5x8_tf,
        u8g2_font_5x7_tf,
        u8g2_font_4x6_tf,        // for the IP address
        u8g2_font_u8glib_4_tf    // absolute smallest fallback
    };

    // Leave 1px margin on each side so the text never touches the border frame.
    int maxTextWidth = widthInPixels - 4;

    const uint8_t* font = fonts[0];
    for (int i = 0; i < 5; i++)
    {
        u8g2.setFont(fonts[i]);
        if (u8g2.getStrWidth(text.c_str()) <= maxTextWidth)
        {
            font = fonts[i];
            break;
        }
    }
    u8g2.setFont(font);

    // Horizontally centered text.
    int textWidth = u8g2.getStrWidth(text.c_str());
    int x = (widthInPixels - textWidth) / 2;

    // Vertically centered text (baseline computed from ascent/descent).
    int ascent  = u8g2.getAscent();
    int descent = u8g2.getDescent();
    int y = (heightInPixels - descent + ascent) / 2;

    u8g2.drawStr(x, y, text.c_str());
    u8g2.drawFrame(0, 0, widthInPixels, heightInPixels);
    u8g2.sendBuffer();
}

void AdafruitSSD1306_64x32::drawBitmap(const unsigned char* bitmap)
{
    u8g2.clearBuffer();
    u8g2.drawXBMP(0, 0, widthInPixels, heightInPixels, bitmap);
    u8g2.sendBuffer();
}