#pragma once
#include <vector>
#include <string>
#include <ArduinoJson.h>
#include "../objects/GroupBlock.hh"

class ProfileParser {
public:
    // Vrací neprázdný vektor při úspěchu.
    // error je nastaven na "" při úspěchu, jinak na popis chyby.
    static std::vector<GroupBlock*> parse(const JsonDocument& doc, std::string& error);
};
