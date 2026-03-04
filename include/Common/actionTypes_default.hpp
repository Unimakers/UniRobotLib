#pragma once
#include <Common/actionType.hpp>
void _movementLoopAction(ActionHandler*parent,std::string arg){
    parent->getMovementAction()->run();
}
bool _movementFinishedAction(ActionHandler*parent,std::string arg){
    return parent->getMovementAction()->getStatus();
}
bool _buzzerFinishedAction(ActionHandler*parent,std::string arg){
    int a = std::stoi(arg);
    if(millis()>=a)return true;
    return false;
}
void _forwardFunc(ActionHandler*parent,DataArgumentType arg){
    parent->getMovementAction()->forward(arg.distance,arg.speed);
    parent->registerLoopAction(_movementLoopAction);
    parent->registerFinishedAction(_movementFinishedAction);
}
void _backwardFunc(ActionHandler*parent,DataArgumentType arg){
    parent->getMovementAction()->backward(arg.distance,arg.speed);
    parent->registerLoopAction(_movementLoopAction);
    parent->registerFinishedAction(_movementFinishedAction);
}
void _turnFunc(ActionHandler*parent,DataArgumentType arg){
    parent->getMovementAction()->turn(arg.angle,arg.speed);
    parent->registerLoopAction(_movementLoopAction);
    parent->registerFinishedAction(_movementFinishedAction);
}
void _turnToFunc(ActionHandler*parent,DataArgumentType arg){
    parent->getMovementAction()->turnTo(arg.angle,arg.speed);
    parent->registerLoopAction(_movementLoopAction);
    parent->registerFinishedAction(_movementFinishedAction);
}
void _moveToFunc(ActionHandler*parent,DataArgumentType arg){
    parent->getMovementAction()->moveTo(arg.target,arg.speed);
    parent->registerLoopAction(_movementLoopAction);
    parent->registerFinishedAction(_movementFinishedAction);
}
void _delayFunc(ActionHandler* parent,DataArgumentType arg){
    parent->registerFinishedAction(_buzzerFinishedAction,std::to_string(millis()+arg.time));
}
void _buzzerFunc(ActionHandler* parent,DataArgumentType arg){
        
}
ActionType FORWARDAction(0,_forwardFunc);
ActionType BACKWARDAction(0,_backwardFunc);
ActionType TURNAction(0,_turnFunc);
ActionType TURN_TOAction(0,_turnToFunc);
ActionType MOVE_TOAction(0,_moveToFunc);
ActionType DELAYAction(0,_delayFunc);
ActionType BUZZERAction(0,_buzzerFunc);
/// @brief predefined default actionTypes list
extern std::map<std::string,ActionType> actionTypes= (std::map<std::string,ActionType>){
    (std::pair<std::string,ActionType>){"FORWARD",FORWARDAction},
    (std::pair<std::string,ActionType>){"BACKWARD",BACKWARDAction},
    (std::pair<std::string,ActionType>){"TURN",TURNAction},
    (std::pair<std::string,ActionType>){"TURN_TO",TURN_TOAction},
    (std::pair<std::string,ActionType>){"MOVE_TO",MOVE_TOAction},
    (std::pair<std::string,ActionType>){"DELAY",DELAYAction},
    (std::pair<std::string,ActionType>){"BUZZER",BUZZERAction}
};