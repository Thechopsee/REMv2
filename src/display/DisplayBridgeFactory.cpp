#include "DisplayBridgeFactory.hh"
#include "ZeroFortyTwo.hh" 
#include "AdafruitSSD1306.hh"
#include "AdafruitSSD1306_64x32.hh"

DisplayBridge* DisplayBridgeFactory::create(DisplayTypeEnum type, int sda, int scl, int reset)
{
    switch (type)
    {
        case ZeroFortyTwo72X40:
            return new ZeroFortyTwo(72, 40, sda, scl, reset);
        case AdafruitSSD1306_64X32:
            return new AdafruitSSD1306_64x32(64, 32, sda, scl, reset);
        case AdafruitSSD1306_128X64:
            return new AdafruitSSD1306(128, 64, sda, scl, reset);
        default:
            return nullptr;
    }
}
