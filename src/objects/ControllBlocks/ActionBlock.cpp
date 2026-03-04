#include "ActionBlock.hh"
#include "../GroupBlock.hh"

extern std::vector<GroupBlock*> Groups;

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

        for (auto group : Groups) {
            for (auto block : group->blocks) {
                if (block != this && this->sharesPinsWith(block)) {
                    block->resetToDefault();
                    block->enabled = false;
                }
            }
        }
    }
    else
    {
        action->Stop();
        this->actual_status="Stopped";

        for (auto group : Groups) {
            for (auto block : group->blocks) {
                if (block != this && this->sharesPinsWith(block)) {
                    bool stillConflict = false;
                    for (auto g2 : Groups) {
                        for (auto b2 : g2->blocks) {
                            if (b2 != block && b2->isRunningAction() && b2->sharesPinsWith(block)) {
                                stillConflict = true;
                                break;
                            }
                        }
                        if (stillConflict) break;
                    }
                    if (!stillConflict) {
                        block->enabled = true;
                    }
                }
            }
        }
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
  return 0;
}

bool ActionBlock::isRunningAction()
{
    return this->actual_status == "Running";
}

void ActionBlock::resetToDefault()
{
    this->setPin(false);
}

