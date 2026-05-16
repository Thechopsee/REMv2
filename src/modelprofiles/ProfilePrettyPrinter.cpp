#include "ProfilePrettyPrinter.hh"

#include "../objects/ControllBlocks/ActionBlock.hh"
#include "../objects/ControllBlocks/InputSliderBlock.hh"
#include "../enums/BlockTypeEnum.hh"

#include <ArduinoJson.h>
#include <string>
#include <vector>

std::string ProfilePrettyPrinter::serialize(const std::vector<GroupBlock*>& groups)
{
    JsonDocument doc;
    JsonArray groupsArray = doc["groups"].to<JsonArray>();

    for (GroupBlock* group : groups)
    {
        JsonObject groupObj = groupsArray.add<JsonObject>();
        groupObj["id"] = group->id;

        // Mapování BlockTypeEnum → string
        const char* typeStr = "controll";
        switch (group->type) {
            case controll:    typeStr = "controll";    break;
            case action:      typeStr = "action";      break;
            case slider:      typeStr = "slider";      break;
            case inputSlider: typeStr = "inputSlider"; break;
            case nav:         typeStr = "nav";         break;
            case status:      typeStr = "status";      break;
            case virt:        typeStr = "virt";        break;
            default:          typeStr = "controll";    break;
        }
        groupObj["type"] = typeStr;

        JsonArray blocksArray = groupObj["blocks"].to<JsonArray>();

        for (BasicBlock* block : group->blocks)
        {
            JsonObject blockObj = blocksArray.add<JsonObject>();
            blockObj["id"] = block->id;
            blockObj["name"] = block->name;

            JsonArray pinsArray = blockObj["pins"].to<JsonArray>();
            for (int pin : block->pins) {
                pinsArray.add(pin);
            }

            // Přidat extra pole podle typu skupiny
            if (group->type == action) {
                ActionBlock* actionBlock = static_cast<ActionBlock*>(block);
                blockObj["actionType"] = actionBlock->getActionTypeName();
            }
            else if (group->type == inputSlider) {
                InputSliderBlock* inputSliderBlock = static_cast<InputSliderBlock*>(block);
                blockObj["maxValue"] = inputSliderBlock->max_value;
            }
        }
    }

    std::string output;
    serializeJsonPretty(doc, output);
    return output;
}
