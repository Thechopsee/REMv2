#pragma once
#include <string>

class DisplayBridge
{
    protected:
    int widthInPixels=0;
    int heightInPixels=0;
    public:

    virtual void clear();
    virtual void write(std::string text);
    virtual void drawBitmap(const unsigned char* bitmap);

    virtual ~DisplayBridge() {}
};