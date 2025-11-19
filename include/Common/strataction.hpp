#pragma once
#include <Common/actionType.hpp>
class StratAction {
    ActionType actionType;
    DataArgumentType arguments;
    public:
    StratAction(ActionType actionType, DataArgumentType arguments){
        this->actionType=actionType;
        this->arguments=arguments;
    }
    void action(ActionHandler* parent){
        this->actionType.action(parent,arguments);
    }
};