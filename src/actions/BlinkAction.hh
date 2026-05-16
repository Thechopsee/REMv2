#pragma once
#include <vector>
#include "Action.hh"

class BlinkAction : public Action {
public:
    const char* getTypeName() const override { return "Blink"; }
protected:
    void ActionBody() override;
};
