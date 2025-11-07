#include "StorageService.hh"
#include <cstdio>   
#include <cstring>  

StorageService* StorageService::instance = nullptr;

StorageService::StorageService(int chipSelectPin) : csPin(chipSelectPin) {}

StorageService* StorageService::getInstance(int chipSelectPin) {
    if (!instance) {
        instance = new StorageService(chipSelectPin);
    }
    return instance;
}

bool StorageService::begin() {
    if (!SD.begin(csPin)) {
        printf("Chyba: SD karta se nepodařilo inicializovat\n");
        return false;
    }
    return true;
}

bool StorageService::appendToFile(const std::string &name, const std::string &data) {
    std::string fileName = name + ".txt";
    File file = SD.open(fileName.c_str(), FILE_APPEND);
    if (!file) {
        printf("Chyba při otevírání souboru: %s\n", fileName.c_str());
        return false;
    }
    file.println(data.c_str());
    file.close();
    return true;
}

std::string StorageService::readFile(const std::string &name) {
    std::string fileName = name + ".txt";
    File file = SD.open(fileName.c_str());
    if (!file) {
        printf("Chyba: soubor neexistuje: %s\n", fileName.c_str());
        return "";
    }

    std::string content;
    while (file.available()) {
        content += static_cast<char>(file.read());
    }
    file.close();
    return content;
}
