#pragma once
#include <vector>
#include "Action.hh"

class LinearBlinkAction : public Action {
public:
    const char* getTypeName() const override { return "LinearBlink"; }
protected:
    void ActionBody() override;
};
