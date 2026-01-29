#pragma once
#include <Arduino.h>

class Action {
private:
    bool inProgress;
    TaskHandle_t taskHandle;
    bool stopRequested;

    static void TaskEntry(void* param);

protected:
    virtual void ActionBody();  
    bool StopRequested() const;

public:
    Action();
    virtual ~Action();
    void Run();
    void Stop();        
    bool GetStatus();   
};
