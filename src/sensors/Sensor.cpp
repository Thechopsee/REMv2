#include "Sensor.hh"

template class Sensor<GyroAcceleratorDataStruct>;

template <typename T>
Sensor<T>::Sensor(std::string name, unsigned long updateInterval, bool enableLogging)
{
    this->name=name;
    this->updateInterval = updateInterval;
    this->loggingEnabled = enableLogging;

}
template <typename T>
void Sensor<T>::SetOnDataChanged(OnDataChanged callback) {
    this->onDataChanged = callback;
}

template <typename T>
void Sensor<T>::ReadValue() {
    if (millis() - lastUpdate >= updateInterval) {
        ReadValueInternal();
        
        if (loggingEnabled && !lastValue.empty()) {
            LogSensorData(lastValue);
        }
        
        if (onDataChanged) {
            onDataChanged(lastValue); // TODO: Pass appropriate data/angle
        }
        
        lastUpdate = millis();
    }
}

template <typename T>
void Sensor<T>::LogSensorData(const std::string& data) {
    if (!loggingEnabled) return;
    
    StorageService* storage = StorageService::getInstance();
    if (!storage) return;
    
    char logEntry[256]; //TODO make this universal for all sensors
    snprintf(logEntry, sizeof(logEntry), "[%lu] %s: %s", millis(), name.c_str(), data.c_str());
    
    std::string fileName = "sensor_log_" + name;
    storage->appendToFile(fileName, logEntry);
}