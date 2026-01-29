#include "ActionBlock.hh"

ActionBlock::ActionBlock(int id, int blok_id, const std::vector<int>& pins, const char* name) : BasicBlock(id,blok_id,pins,name)
{
    this->actual_status="Stopped";
    for (int p : this->pins) {
        pinMode(p, OUTPUT);
    }
    this->action=new Action();
}
void ActionBlock::setPin(bool dat)
{
    if(dat)
    {
        action->Run();
        this->actual_status="Running";
    }
    else
    {
        action->Stop();
        this->actual_status="Stopped";
    }
}
void ActionBlock::update()
{
    /*int value=current_value;
    if(value!=0)
    {
        this->actual_status="🟢";
    }
    else
    {
        this->actual_status="🔴";
    }

    for (int p : this->pins) {
        digitalWrite(p,value);
    }*/
    
}
void ActionBlock::resolveInput(String request)
{
        std::string nameoff="/";
        nameoff.append(this->name);
        nameoff.append("=OFF");
        
        std::string nameon="/";
        nameon.append(this->name);
        nameon.append("=ON");
        
        if(request.indexOf(nameoff.c_str())!=-1)
        {
            this->setPin(false);
        }
        if(request.indexOf(nameon.c_str())!=-1)
        {
            this->setPin(true);
        }
}
int ActionBlock::getValue()
{
  return this->current_value;
}


