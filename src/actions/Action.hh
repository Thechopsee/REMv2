#pragma once
#include <Arduino.h>

class Action {
private:
    bool inProgress;
    TaskHandle_t taskHandle;

    static void TaskEntry(void* param);

protected:
    virtual void ActionBody();  

public:
    Action();
    virtual ~Action();
    void Run();        
    bool GetStatus();   
};
