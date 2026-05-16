#include "ProfileParser.hh"

#include "../actions/LinearBlinkAction.hh"
#include "../actions/BlinkAction.hh"
#include "../actions/RandomBlinkAction.hh"

#include "../objects/ControllBlocks/OnOffBlock.hh"
#include "../objects/ControllBlocks/ActionBlock.hh"
#include "../objects/ControllBlocks/SliderBlock.hh"
#include "../objects/ControllBlocks/InputSliderBlock.hh"
#include "../enums/BlockTypeEnum.hh"

#include <string>
#include <vector>

std::vector<GroupBlock*> ProfileParser::parse(const JsonDocument& doc, std::string& error)
{
    error = "";
    std::vector<GroupBlock*> groups;

    JsonArrayConst groupsArray = doc["groups"].as<JsonArrayConst>();

    for (JsonObjectConst groupObj : groupsArray)
    {
        int groupId = groupObj["id"].as<int>();
        const char* typeStr = groupObj["type"].as<const char*>();

        BlockTypeEnum blockType;
        bool typeKnown = true;

        if (strcmp(typeStr, "controll") == 0) {
            blockType = controll;
        } else if (strcmp(typeStr, "action") == 0) {
            blockType = action;
        } else if (strcmp(typeStr, "slider") == 0) {
            blockType = slider;
        } else if (strcmp(typeStr, "inputSlider") == 0) {
            blockType = inputSlider;
        } else {
            typeKnown = false;
        }

        if (!typeKnown) {
            // Uvolnit již alokované skupiny
            for (GroupBlock* g : groups) {
                for (BasicBlock* b : g->blocks) {
                    delete b;
                }
                delete g;
            }
            error = std::string("Unknown group type: ") + typeStr;
            return {};
        }

        GroupBlock* group = new GroupBlock(groupId, blockType);

        JsonArrayConst blocksArray = groupObj["blocks"].as<JsonArrayConst>();

        for (JsonObjectConst blockObj : blocksArray)
        {
            int blockId = blockObj["id"].as<int>();
            const char* blockName = blockObj["name"].as<const char*>();

            // Načíst pins
            std::vector<int> pins;
            JsonArrayConst pinsArray = blockObj["pins"].as<JsonArrayConst>();
            for (JsonVariantConst pin : pinsArray) {
                pins.push_back(pin.as<int>());
            }

            BasicBlock* block = nullptr;

            if (blockType == controll) {
                block = new OnOffBlock(blockId, 0, pins, blockName);
            }
            else if (blockType == action) {
                const char* actionTypeStr = blockObj["actionType"].as<const char*>();
                Action* act = nullptr;

                if (actionTypeStr != nullptr) {
                    if (strcmp(actionTypeStr, "LinearBlink") == 0) {
                        act = new LinearBlinkAction();
                    } else if (strcmp(actionTypeStr, "Blink") == 0) {
                        act = new BlinkAction();
                    } else if (strcmp(actionTypeStr, "RandomBlink") == 0) {
                        act = new RandomBlinkAction();
                    }
                }

                if (act != nullptr) {
                    block = new ActionBlock(blockId, 0, pins, blockName, act);
                } else {
                    block = new ActionBlock(blockId, 0, pins, blockName);
                }
            }
            else if (blockType == slider) {
                block = new SliderBlock(blockId, 0, pins, blockName);
            }
            else if (blockType == inputSlider) {
                int maxValue = 180;
                if (blockObj.containsKey("maxValue")) {
                    maxValue = blockObj["maxValue"].as<int>();
                }
                block = new InputSliderBlock(blockId, 0, pins, blockName, maxValue);
            }

            if (block != nullptr) {
                group->blocks.push_back(block);
            }
        }

        groups.push_back(group);
    }

    return groups;
}
