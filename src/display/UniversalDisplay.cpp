#include "UniversalDisplay.hh"

UniversalDisplay :: UniversalDisplay(DisplayTypeEnum display)
{
    bridge=DisplayBridgeFactory::create(display);
}