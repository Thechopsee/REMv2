#include "DisplayBridgeFactory.hh"
#include "ZeroFortyTwo.hh" 
#include "AdafruitSSD1306.hh"

DisplayBridge* DisplayBridgeFactory::create(DisplayTypeEnum type)
{
    switch (type)
    {
        case ZeroFortyTwo72X40:
            return new ZeroFortyTwo(72,40);
        case AdafruitSSD1306_128X64:
            return new AdafruitSSD1306(128,64);
        default:
            return nullptr;
    }
}
