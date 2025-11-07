#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

class StorageService {
private:
    const int csPin;
    static StorageService* instance;

    StorageService(int chipSelectPin);

public:
    StorageService(const StorageService&) = delete;
    StorageService& operator=(const StorageService&) = delete;

    static StorageService* getInstance(int chipSelectPin = 5);
    bool begin();
    
    bool appendToFile(const std::string &name, const std::string &data);
    std::string readFile(const std::string &name);
};

