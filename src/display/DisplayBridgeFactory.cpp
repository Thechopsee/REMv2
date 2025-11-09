#include "DisplayBridgeFactory.hh"
#include "ZeroFortyTwo.hh" 

DisplayBridge* DisplayBridgeFactory::create(DisplayTypeEnum type)
{
    switch (type)
    {
        case ZeroFortyTwo72X40:
            return new ZeroFortyTwo(72,40);
        default:
            return nullptr;
    }
}
