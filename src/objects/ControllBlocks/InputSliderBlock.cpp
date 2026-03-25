#include "InputSliderBlock.hh"

InputSliderBlock::InputSliderBlock(int id, int blok_id, const std::vector<int>& pins, const char* name, int max_val, int default_value) : BasicBlock(id,blok_id,pins,name)
{
    this->default_value = default_value;
    this->current_value = default_value;
    this->max_value = max_val;
    this->actual_status = std::to_string(default_value);
    for (int p : this->pins) {
        pinMode(p, OUTPUT);
        int pwmValue = map(default_value, 0, max_value, 0, 255);
        analogWrite(p, pwmValue);
    }
}

void InputSliderBlock::setValue(int val)
{
    this->enabled = true;
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

void InputSliderBlock::resetToDefault()
{
    this->enabled = false;
    this->current_value = this->default_value;
    this->actual_status = std::to_string(this->default_value);
    for (int p : this->pins) {
        pinMode(p, OUTPUT);
        digitalWrite(p, this->default_value != 0 ? HIGH : LOW);
    }
}

void InputSliderBlock::resolveInput(String request)
{
}

int InputSliderBlock::getValue()
{
    return this->current_value;
}
