#pragma once
#include <Common/strategie.hpp>
class ActionHandler{
    public:
    ActionHandler();
    void setup(Strategie strat);
    bool checkActionFinished();
    void nextAction();
    void loop();
};