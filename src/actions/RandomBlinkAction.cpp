#include <vector>
#include <algorithm>
#include <Arduino.h>

#include "Action.hh"

class RandomBlinkAction : public Action {
protected:
    void ActionBody() override {
        std::vector<int> pins = GetPins();
        if (pins.empty()) {
            return;
        }

        randomSeed(esp_random());

        while (!StopRequested()) {
            std::random_shuffle(pins.begin(), pins.end());

            for (int pin : pins) {
                if (StopRequested()) return;

                digitalWrite(pin, HIGH);
                vTaskDelay(500 / portTICK_PERIOD_MS);
                digitalWrite(pin, LOW);
                vTaskDelay(500 / portTICK_PERIOD_MS);
            }
        }
    }
};
