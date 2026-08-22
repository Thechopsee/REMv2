#include "UniversalDisplay.hh"
#include <WiFi.h>

UniversalDisplay :: UniversalDisplay(DisplayTypeEnum display, int sda, int scl, int reset)
{
    bridge=DisplayBridgeFactory::create(display, sda, scl, reset);
}

void UniversalDisplay ::drawBitmap(const unsigned char* bitmap)
{
    bridge->drawBitmap(bitmap);
}

void UniversalDisplay ::write(std::string text)
{
    if (WiFi.status() == WL_CONNECTED) {
        String ip = WiFi.localIP().toString();
        size_t pos = text.find("REM");
        if (pos != std::string::npos) {
            text.replace(pos, 3, ip.c_str());
        }
    }
    bridge->write(text);
}

void UniversalDisplay ::clear()
{
    bridge->clear();
}