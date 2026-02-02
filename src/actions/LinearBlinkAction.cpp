#pragma once
#include <vector>

#include "Action.hh"

class LinearBlinkAction : public Action {
protected:
    void ActionBody() override {
        std::vector<int> pins = {2, 4, 5, 18, 19}; //TODO handle pins properly
        while (!StopRequested()) {
            for (int pin : pins) {
                digitalWrite(pin, HIGH);
                vTaskDelay(500 / portTICK_PERIOD_MS);
                digitalWrite(pin, LOW);
                vTaskDelay(500 / portTICK_PERIOD_MS);
            }
        }
    }
};