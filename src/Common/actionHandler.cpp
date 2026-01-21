#include <Common/actionHandler.hpp>
ActionHandler::ActionHandler()
{
}
void ActionHandler::setup(RobotConfig config,CommunicationCartePrincipale* communication)
{
    this->config = config;
    this->strategie = config.strategie;
    this->initStrategie = config.initStrategie;
    this->communication=communication;
}
bool ActionHandler::checkActionFinished()
{
    return true;
}
void ActionHandler::nextAction()
{
}
void ActionHandler::loop()
{
    if(getState()==STATE::FINISHED)return;
    if(this->communication!=nullptr)this->communication->loop();
    Strategie theStrat = this->initStrategie;
    if(getState() == STATE::RUNNING){
        if(checkActionFinished())return setState(STATE::IDLE);
        
    }
    else if(getState() == STATE::IDLE){
        if(this->currentActionIndex+1>=theStrat.size()){
            if(curStrat==CURRENT_STRAT::INIT){
                curStrat=CURRENT_STRAT::RUN;
                currentActionIndex=0;
                return setState(STATE::IDLE);
            }
            return setState(STATE::FINISHED);
        }
        theStrat.call(this->currentActionIndex,this);
        this->currentActionIndex++;
        return setState(STATE::RUNNING);
    }else if (getState() == STATE::PAUSED){

    }else{
        // WHAT ?
        return setState(STATE::IDLE);
    }
}