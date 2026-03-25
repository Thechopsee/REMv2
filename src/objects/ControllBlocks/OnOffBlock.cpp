#include "OnOffBlock.hh"

OnOffBlock::OnOffBlock(int id, int blok_id, const std::vector<int>& pins, const char* name, int default_value) : BasicBlock(id,blok_id,pins,name)
{
    this->default_value = default_value;
    this->current_value = default_value;
    this->actual_status = (default_value != 0) ? "🟢" : "🔴";
    for (int p : this->pins) {
        pinMode(p, OUTPUT);
        digitalWrite(p, default_value);
    }
}
void OnOffBlock::setPin(bool dat)
{
    this->enabled = true;
    this->current_value = dat ? HIGH : LOW;
    if(dat)
    {
        for (int p : this->pins) {
        pinMode(p, OUTPUT);
        digitalWrite(p, HIGH);
        }
        this->actual_status="🟢";
    }
    else
    {
        for (int p : this->pins) {
        pinMode(p, OUTPUT);
        digitalWrite(p, LOW);
        }
        this->actual_status="🔴";
    }
}
void OnOffBlock::update()
{
    if (!this->enabled) return;

    int value=current_value;
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
    }
    
}
void OnOffBlock::resetToDefault()
{
    this->enabled = false;
    this->current_value = this->default_value;
    this->actual_status = (this->default_value != 0) ? "🟢" : "🔴";
    for (int p : this->pins) {
        pinMode(p, OUTPUT);
        digitalWrite(p, this->default_value);
    }
}
void OnOffBlock::resolveInput(String request)
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
int OnOffBlock::getValue()
{
  return this->current_value;
}


