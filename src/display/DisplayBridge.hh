#pragma once
#include <string>

class DisplayBridge
{
    protected:
    int widthInPixels=0;
    int heightInPixels=0;
    public:

    virtual void clear() = 0;
    virtual void write(std::string text) = 0;
    virtual void drawBitmap(const unsigned char* bitmap) = 0;

    virtual ~DisplayBridge() {}
};