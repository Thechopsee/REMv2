#pragma once 

#include "../display/UniversalDisplay.hh"
#include "../display/bitmaps/boatBitmap.hh"
#include <Arduino.h>
#include <stdlib.h>

//TODO make it universal and split this to concrete class
class DataDrivenEvent{
    public:
    static void OnDataChanged(UniversalDisplay* display, std::string data)
    {
        int ax = 0, ay = 0, az = 0;
        sscanf(data.c_str(), "AX:%d AY:%d AZ:%d", &ax, &ay, &az);
        float angle = atan2(ay, sqrt(ax*ax + az*az)) * 180.0 / PI;
        
        if (angle < 0) angle += 360;
        
        if(angle < 45)
        {
            display->drawBitmap(boat);
        }
        else if(angle >= 45 && angle < 90)
        {
            display->drawBitmap(boat_45);
        }
        else if(angle >= 90 && angle < 225)
        {
            display->drawBitmap(boat_90);
        }
        else if(angle >= 225 && angle < 270)
        {
            display->drawBitmap(boat_225);
        }
        else
        {
            display->drawBitmap(boat_270);
        }
    }
};