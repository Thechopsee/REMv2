#include "Sensor.hh"

template class Sensor<GyroAcceleratorDataStruct>;

template <typename T>
Sensor<T>::Sensor(std::string name, unsigned long updateInterval)
{
    this->name=name;
    this->updateInterval = updateInterval;

}
template <typename T>
void Sensor<T>::SetOnDataChanged(OnDataChanged callback) {
    this->onDataChanged = callback;
}