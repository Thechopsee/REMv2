#include "OnOffBlock.hh"

OnOffBlock::OnOffBlock(int id, int blok_id, const std::vector<int>& pins, char* name) : BasicBlock(id,blok_id,pins,name)
{
    this->actual_status="🔴";
    for (int p : this->pins) {
        pinMode(p, OUTPUT);
    }
}
void OnOffBlock::setPin(bool dat)
{
    if(dat)
    {
        for (int p : this->pins) {
        digitalWrite(p, HIGH);
        }
        this->actual_status="🟢";
    }
    else
    {
        for (int p : this->pins) {
        digitalWrite(p, LOW);
        }
        this->actual_status="🔴";
    }
}
void OnOffBlock::update()
{
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


