#include "SliderBlock.hh"

SliderBlock::SliderBlock(int id, int blok_id, const std::vector<int>& pins, const char* name, int default_value) : BasicBlock(id,blok_id,pins,name)
{
    this->default_value = default_value;
    this->current_value = default_value;
    this->actual_status = std::to_string(default_value);
    for (int p : this->pins) {
        pinMode(p, OUTPUT);
        int pwmValue = map(default_value, 0, 100, 0, 255);
        analogWrite(p, pwmValue);
    }
}

void SliderBlock::setValue(int val)
{
    this->enabled = true;
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

void SliderBlock::resetToDefault()
{
    this->enabled = false;
    this->current_value = this->default_value;
    this->actual_status = std::to_string(this->default_value);
    int pwmValue = map(this->default_value, 0, 100, 0, 255);
    for (int p : this->pins) {
        analogWrite(p, pwmValue);
    }
}

void SliderBlock::resolveInput(String request)
{
}

int SliderBlock::getValue()
{
    return this->current_value;
}
