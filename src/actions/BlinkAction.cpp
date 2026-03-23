#include "Action.hh"

class BlinkAction : public Action {
protected:
    void ActionBody() override {
        while (!StopRequested()) {
            std::vector<int> pins = GetPins();
                if (pins.empty()) {
                    return;
                }
            for (int pin : pins) {
                digitalWrite(pin, HIGH);
                
            }
            vTaskDelay(500 / portTICK_PERIOD_MS);
            for (int pin : pins) {
                digitalWrite(pin, LOW);
            }
            vTaskDelay(500 / portTICK_PERIOD_MS);
            if (StopRequested()) return;
    }
    }
};