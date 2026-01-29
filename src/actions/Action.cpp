#include "Action.hh"

Action::Action() : inProgress(false),stopRequested(false), taskHandle(nullptr) {}

Action::~Action() {
    if (taskHandle != nullptr) {
        vTaskDelete(taskHandle);
    }
}

void Action::TaskEntry(void* param) {
    Action* self = static_cast<Action*>(param);
    self->ActionBody();            
    self->inProgress = false;    
    self->taskHandle = nullptr;
    vTaskDelete(nullptr);         
}

void Action::Run() {
    if (inProgress) return;  
    stopRequested = false;
    inProgress = true;

    xTaskCreatePinnedToCore(
        TaskEntry,         
        "ActionTask",     
        4096,              
        this,            
        1,                 
        &taskHandle,       
        APP_CPU_NUM       
    );
}

void Action::Stop() {
    stopRequested = true;
}

bool Action::StopRequested() const {
    return stopRequested;
}

bool Action::GetStatus() {
    return inProgress;
}

void Action::ActionBody() {
}
