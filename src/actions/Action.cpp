#include "Action.hh"

Action::Action() : inProgress(false), taskHandle(nullptr) {}

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

bool Action::GetStatus() {
    return inProgress;
}

void Action::ActionBody() {
}
