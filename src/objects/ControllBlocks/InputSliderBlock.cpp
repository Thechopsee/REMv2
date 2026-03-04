#include "InputSliderBlock.hh"

InputSliderBlock::InputSliderBlock(int id, int blok_id, const std::vector<int>& pins, const char* name, int max_val, int default_val) : BasicBlock(id,blok_id,pins,name)
{
    this->defaultValue = default_val;
    this->current_value = default_val;
    this->max_value = max_val;
    this->actual_status = std::to_string(default_val);
    for (int p : this->pins) {
        pinMode(p, OUTPUT);
    }
}

void InputSliderBlock::setValue(int val)
{
    if (val < 0) val = 0;
    if (val > max_value) val = max_value;
    this->current_value = val;
    this->actual_status = std::to_string(val);

    int pwmValue = map(val, 0, max_value, 0, 255);
    for (int p : this->pins) {
        analogWrite(p, pwmValue);
    }
}

void InputSliderBlock::update()
{
}

void InputSliderBlock::resolveInput(String request)
{
}

int InputSliderBlock::getValue()
{
    return this->current_value;
}

void InputSliderBlock::resetToDefault()
{
    this->setValue(this->defaultValue);
}
