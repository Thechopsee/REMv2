#include "SliderBlock.hh"

SliderBlock::SliderBlock(int id, int blok_id, const std::vector<int>& pins, const char* name) : BasicBlock(id,blok_id,pins,name)
{
    this->current_value = 0;
    this->actual_status = "0";
    for (int p : this->pins) {
        pinMode(p, OUTPUT);
    }
}

void SliderBlock::setValue(int val)
{
    if (val < 0) val = 0;
    if (val > 100) val = 100;
    this->current_value = val;
    this->actual_status = std::to_string(val);

    int pwmValue = map(val, 0, 100, 0, 255);
    for (int p : this->pins) {
        analogWrite(p, pwmValue);
    }
}

void SliderBlock::update()
{
}

void SliderBlock::resolveInput(String request)
{
}

int SliderBlock::getValue()
{
    return this->current_value;
}
