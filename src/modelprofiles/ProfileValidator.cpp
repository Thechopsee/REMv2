#include "ProfileValidator.hh"

static const char* VALID_ACTION_TYPES[] = {"LinearBlink", "Blink", "RandomBlink"};
static const int VALID_ACTION_TYPES_COUNT = 3;

static bool isValidActionType(const char* actionType) {
    for (int i = 0; i < VALID_ACTION_TYPES_COUNT; i++) {
        if (strcmp(actionType, VALID_ACTION_TYPES[i]) == 0) {
            return true;
        }
    }
    return false;
}

std::string ProfileValidator::validate(const JsonDocument& doc) {
    // Ověřit přítomnost kořenového pole groups
    if (!doc.containsKey("groups") || !doc["groups"].is<JsonArrayConst>()) {
        return "Missing or invalid root field: groups";
    }

    JsonArrayConst groups = doc["groups"].as<JsonArrayConst>();

    for (size_t gi = 0; gi < groups.size(); gi++) {
        JsonObjectConst group = groups[gi];
        std::string groupPath = "groups[" + std::to_string(gi) + "]";

        // Ověřit přítomnost id skupiny
        if (!group.containsKey("id")) {
            return "Missing field: " + groupPath + ".id";
        }

        // Ověřit přítomnost type skupiny
        if (!group.containsKey("type") || !group["type"].is<const char*>()) {
            return "Missing or invalid field: " + groupPath + ".type";
        }

        // Ověřit přítomnost blocks skupiny
        if (!group.containsKey("blocks") || !group["blocks"].is<JsonArrayConst>()) {
            return "Missing or invalid field: " + groupPath + ".blocks";
        }

        const char* groupType = group["type"].as<const char*>();
        JsonArrayConst blocks = group["blocks"].as<JsonArrayConst>();

        for (size_t bi = 0; bi < blocks.size(); bi++) {
            JsonObjectConst block = blocks[bi];
            std::string blockPath = groupPath + ".blocks[" + std::to_string(bi) + "]";

            // Ověřit přítomnost id bloku
            if (!block.containsKey("id")) {
                return "Missing field: " + blockPath + ".id";
            }

            // Ověřit přítomnost name bloku
            if (!block.containsKey("name") || !block["name"].is<const char*>()) {
                return "Missing or invalid field: " + blockPath + ".name";
            }

            // Ověřit přítomnost pins bloku
            if (!block.containsKey("pins") || !block["pins"].is<JsonArrayConst>()) {
                return "Missing or invalid field: " + blockPath + ".pins";
            }

            JsonArrayConst pins = block["pins"].as<JsonArrayConst>();

            // Ověřit, že pins je neprázdné pole
            if (pins.size() == 0) {
                return "Field must not be empty: " + blockPath + ".pins";
            }

            // Ověřit, že všechny prvky pins jsou celá čísla
            for (size_t pi = 0; pi < pins.size(); pi++) {
                if (!pins[pi].is<int>()) {
                    return "Non-integer value in: " + blockPath + ".pins[" + std::to_string(pi) + "]";
                }
            }

            // Pro skupiny typu action ověřit přítomnost actionType s platnou hodnotou
            if (strcmp(groupType, "action") == 0) {
                if (!block.containsKey("actionType") || !block["actionType"].is<const char*>()) {
                    return "Missing or invalid field: " + blockPath + ".actionType";
                }

                const char* actionType = block["actionType"].as<const char*>();
                if (!isValidActionType(actionType)) {
                    return "Invalid actionType value \"" + std::string(actionType) + "\" at: " + blockPath + ".actionType";
                }
            }
        }
    }

    return "";
}
