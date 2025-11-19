#pragma once
#include <Common/strataction.hpp>
#include <vector>
#include <map>
class Strategie{
    std::vector<StratAction> stratlist;
    public:
    Strategie* add(StratAction stratAction){
        this->stratlist.push_back(stratAction);
        return this;
    }
    Strategie* add(ActionType actType, DataArgumentType args){
        StratAction strata(actType,args);
        return this->add(strata);
    }
    Strategie* add(std::string predefinedTypeName, DataArgumentType args){
        ActionType actType = (actionTypes.count(predefinedTypeName)!=0)?actionTypes[predefinedTypeName]:ActionType();
        return this->add(actType,args);
    }
    
};