#include "RealTimeService.hh"

RealTimeService* RealTimeService::instance = nullptr;

RealTimeService::RealTimeService() {}

RealTimeService* RealTimeService::getInstance() {
    if (!instance) {
        instance = new RealTimeService();
        instance->begin();
    }
    return instance;
}

bool RealTimeService::begin() {
    configTzTime(
        TZ_INFO,
        "pool.ntp.org",
        "time.nist.gov"
    );

    Serial.println("Waiting for NTP time...");

    time_t now = 0;
    int retry = 0;
    const int retryCount = 20;

    while (now < 100000 && retry < retryCount) {
        delay(500);
        time(&now);
        retry++;
    }

    if (now < 100000) {
        Serial.println("Failed to obtain time");
        return false;
    }

    Serial.println("Time synchronized");
    return true;
}

time_t RealTimeService::now() {
    return time(nullptr);
}

std::string RealTimeService::nowAsString() {
    time_t rawTime = time(nullptr);
    struct tm timeInfo;
    localtime_r(&rawTime, &timeInfo);

    char buffer[25];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);

    return std::string(buffer);
}
