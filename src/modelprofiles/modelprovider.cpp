#include "modelprovider.hh"
#include "R18ModelProfile.hh"
#include "ProfileValidator.hh"
#include "ProfileParser.hh"
#include "../service/StorageService.hh"
#include <ArduinoJson.h>
#include <Arduino.h>

ModelProvider::ModelProvider()
{
    modelProfile = new R18ModelProfile();
    this->LoadModel();
}

void ModelProvider::freeGroups()
{
    for (GroupBlock* group : this->Groups) {
        for (BasicBlock* block : group->blocks) {
            delete block;
        }
        delete group;
    }
    this->Groups.clear();
}

void ModelProvider::LoadModel()
{
    StorageService* storage = StorageService::getInstance();
    std::string profileJson = storage->readFile("model-profile");

    if (!profileJson.empty()) {
        std::string err = this->LoadFromJson(profileJson);
        if (err.empty()) {
            return;
        }
        Serial.print("[ModelProvider] Failed to load profile from SD: ");
        Serial.println(err.c_str());
    }

    // Fallback na výchozí R18ModelProfile
    this->Groups = modelProfile->LoadModel();
}

std::vector<GroupBlock*> ModelProvider::GetGroups()
{
    return this->Groups;
}

std::string ModelProvider::LoadFromJson(const std::string& json)
{
    JsonDocument doc;
    DeserializationError parseErr = deserializeJson(doc, json);
    if (parseErr) {
        return std::string("JSON parse error: ") + parseErr.c_str();
    }

    std::string validationErr = ProfileValidator::validate(doc);
    if (!validationErr.empty()) {
        return validationErr;
    }

    std::string parseError;
    std::vector<GroupBlock*> newGroups = ProfileParser::parse(doc, parseError);
    if (!parseError.empty()) {
        return parseError;
    }

    freeGroups();
    this->Groups = newGroups;
    return "";
}
