#include "UniversalDisplay.hh"

UniversalDisplay :: UniversalDisplay(DisplayTypeEnum display)
{
    bridge=DisplayBridgeFactory::create(display);
}

void UniversalDisplay ::drawBitmap(const unsigned char* bitmap)
{
    bridge->drawBitmap(bitmap);
}