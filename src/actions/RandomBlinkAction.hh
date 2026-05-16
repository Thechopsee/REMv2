#pragma once
#include <vector>
#include <algorithm>
#include "Action.hh"

class RandomBlinkAction : public Action {
public:
    const char* getTypeName() const override { return "RandomBlink"; }
protected:
    void ActionBody() override;
};
