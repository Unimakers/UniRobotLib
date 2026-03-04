#pragma once
#include <Common/strataction.hpp>
#include <vector>
#include <map>
#include <Common/actionTypes_default.hpp>
class Strategie{
    std::vector<StratAction> stratlist;
    public:
    Strategie(){
    }
    Strategie* add(StratAction stratAction){
        this->stratlist.push_back(stratAction);
        return this;
    }
    Strategie* add(ActionType actType, DataArgumentType args){
        StratAction strata(actType,args);
        return this->add(strata);
    }
    Strategie* add(std::string predefinedTypeName, DataArgumentType args){
        ActionType actType = (actionTypes.count(predefinedTypeName)!=0)?*actionTypes[predefinedTypeName]:ActionType();
        return this->add(actType,args);
    }
    int size(){
        return this->stratlist.size();
    }
    StratAction get(int idx){
        return this->stratlist[idx];
    }
    void call(int idx,ActionHandler* parent){
        this->get(idx).action(parent);
    }
    
    // default actions
    Strategie* FORWARD(double distance, int speed){
        return this->add("FORWARD",(DataArgumentType){.speed=speed,.distance=distance});
    }
    Strategie* BACKWARD(double distance, int speed){
        return this->add("BACKWARD",(DataArgumentType){.speed=speed,.distance=distance});
    }
    Strategie* TURN(double angle, int speed){
        return this->add("TURN",(DataArgumentType){.speed=speed,.angle=angle});
    }
    Strategie* TURN_TO(double angle, int speed){
        return this->add("TURN_TO",(DataArgumentType){.speed=speed,.angle=angle});
    }
    Strategie* MOVE_TO(Coord coord, int speed){
        return this->add("MOVE_TO",(DataArgumentType){.speed=speed,.target=coord});
    }
    Strategie* DELAY(int miliseconds){
        return this->add("DELAY",(DataArgumentType){.time=miliseconds});
    }
};