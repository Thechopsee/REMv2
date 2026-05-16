#pragma once
#include <Arduino.h>
#include <vector>

class Action {
private:
    bool inProgress;
    TaskHandle_t taskHandle;
    bool stopRequested;

    static void TaskEntry(void* param);

protected:
    std::vector<int> pins;
    virtual void ActionBody();  
    bool StopRequested() const;
    const std::vector<int>& GetPins() const;

public:
    Action();
    virtual ~Action();
    void Run();
    void Stop();        
    bool GetStatus();   
    void SetPins(const std::vector<int>& pins);
    virtual const char* getTypeName() const { return "Action"; }
};
