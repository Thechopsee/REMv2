#include "TextSensorBlock.hh"

TextSensorBlock::TextSensorBlock(int id, int blok_id,const std::vector<int>& pins, const char* name,Sensor* sensor) : BasicBlock(id,blok_id,pins,name)
{
    this->sensor=sensor;
}
void TextSensorBlock::setPin(bool dat) {
    return;
}

void TextSensorBlock::resolveInput(String request) {
    return;
}

void TextSensorBlock::update() {
    this->current_value = this->sensor->lastValue;
}

String TextSensorBlock::getValue() {
    return this->current_value;
}