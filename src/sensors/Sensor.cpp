#include "Sensor.hh"

Sensor::Sensor(std::string name, unsigned long updateInterval)
{
    this->name=name;
    this->updateInterval = updateInterval;

}

void Sensor::SetOnDataChanged(OnDataChanged callback) {
    this->onDataChanged = callback;
}