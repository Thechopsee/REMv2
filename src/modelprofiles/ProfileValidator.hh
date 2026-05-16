#pragma once
#include <string>
#include <ArduinoJson.h>

class ProfileValidator {
public:
    // Vrací "" při úspěchu, jinak popis první nalezené chyby (včetně cesty k problematickému poli)
    static std::string validate(const JsonDocument& doc);
};
