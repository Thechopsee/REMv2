#include "TextSensorBlock.hh"

template class TextSensorBlock<GyroAcceleratorDataStruct>;

template <typename T>
TextSensorBlock<T>::TextSensorBlock(int id, int blok_id,const std::vector<int>& pins, const char* name,Sensor<T>* sensor) : BasicBlock(id,blok_id,pins,name)
{
    this->sensor=sensor;
}
template <typename T>
void TextSensorBlock<T>::setPin(bool dat) {
    return;
}
template <typename T>
void TextSensorBlock<T>::resolveInput(String request) {
    return;
}
template <typename T>
void TextSensorBlock<T>::update() {
    this->actual_status = this->sensor->lastValue;
    this->current_value = this->sensor->lastValue;
}
template <typename T>
std::string TextSensorBlock<T>::getValue() {
    return this->current_value;
}