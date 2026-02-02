#pragma once
#include <string>
#include <time.h>
#include <Arduino.h>

#include "../config/env.hh"

class RealTimeService {
private:
    static RealTimeService* instance;
    RealTimeService();

public:
    static RealTimeService* getInstance();

    bool begin();
    time_t now();
    std::string nowAsString();
};
