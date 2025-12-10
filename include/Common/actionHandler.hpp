#pragma once
#include <Common/communication.hpp>
#include <Common/robotConfig.hpp>
class ActionHandler{
    enum struct STATE{
        IDLE,
        RUNNING,
        PAUSED,
        FINISHED
    };
    enum struct CURRENT_STRAT{
        INIT,RUN
    };
    STATE state = STATE::IDLE;
    CURRENT_STRAT curStrat = CURRENT_STRAT::INIT;
    RobotConfig config;
    CommunicationCartePrincipale* communication=nullptr;
    Strategie strategie,initStrategie;
    int currentActionIndex=0;
    public:
    ActionHandler();
    void setup(RobotConfig config,CommunicationCartePrincipale* communication);
    bool checkActionFinished();
    void nextAction();
    void loop();
    STATE getState(){return this->state;}
    void setState(STATE newState){this->state=newState;}
    CustomDataConfigType getConfigValue(std::string name){return this->config.get(name);}
    void setConfigValue(std::string name, CustomDataConfigType value){this->config.set(name,value);}
};