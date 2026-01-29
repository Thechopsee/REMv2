#include "Action.hh"

class BlinkAction : public Action {
protected:
    void ActionBody() override {
        while (!StopRequested()) {
        for (int i = 0; i < 5; i++) {
            digitalWrite(2, HIGH);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            digitalWrite(2, LOW);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }
    }
};