#include "../display/UniversalDisplay.hh"
#include "../display/bitmaps/boatBitmap.hh"
class DataDrivenEvent{
    public:
    static void OnDataChanged(UniversalDisplay* display,int angle)
    {
        if(angle<45)
        {
            display->drawBitmap(boat);
        }
        else if(angle>45 && angle<90)
        {
            display->drawBitmap(boat_45);
        }
        else if(angle>90 && angle<225)
        {
            display->drawBitmap(boat_90);
        }
        else if(angle>225 && angle<270)
        {
            display->drawBitmap(boat_225);
        }
        else
        {
            display->drawBitmap(boat_270);
        }
    }
}