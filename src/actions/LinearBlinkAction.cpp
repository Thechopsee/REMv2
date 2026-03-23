#pragma once
#include <vector>

#include "Action.hh"

class LinearBlinkAction : public Action {
protected:
    void ActionBody() override {
        const std::vector<int>& pins = GetPins();
        if (pins.empty()) {
            return;
        }
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
