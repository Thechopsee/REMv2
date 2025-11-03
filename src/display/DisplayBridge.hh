#pragma once

class DisplayBridge
{
    private:
    int widthInPixels=0;
    int heightInPixels=0;
    public:

    virtual void clear();
    virtual void write();

    virtual ~DisplayBridge() {}
};