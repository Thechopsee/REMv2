#include "DisplayBridgeFactory.hh"
#include "ZeroNine.hh" 

DisplayBridge* DisplayBridgeFactory::create(DisplayTypeEnum type)
{
    switch (type)
    {
        case ZeroNine128x96:
            return new ZeroNine();
        default:
            return nullptr;
    }
}
