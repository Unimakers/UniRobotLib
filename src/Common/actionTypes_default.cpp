#include <Common/actionTypes_default.hpp>
#ifndef HELLOWORLD_ACT_DEF_C
#define HELLOWORLD_ACT_DEF_C 1
#include <Common/actionHandler.hpp>

ActionType *FORWARDAction = nullptr;
ActionType *BACKWARDAction = nullptr;
ActionType *TURNAction = nullptr;
ActionType *TURN_TOAction = nullptr;
ActionType *MOVE_TOAction = nullptr;
ActionType *DELAYAction = nullptr;
ActionType *BUZZERAction = nullptr;
std::map<std::string, ActionType *> actionTypes;

void _movementLoopAction(ActionHandler *parent, std::string arg)
{
    parent->getMovementAction()->run();
}
bool _movementFinishedAction(ActionHandler *parent, std::string arg)
{
    return parent->getMovementAction()->getStatus();
}
bool _buzzerFinishedAction(ActionHandler *parent, std::string arg)
{
    int a = std::stoi(arg);
    if (millis() >= a)
        return true;
    return false;
}
void _forwardFunc(ActionHandler *parent, DataArgumentType arg)
{
    parent->getMovementAction()->forward(arg.distance, arg.speed);
    parent->registerLoopAction(_movementLoopAction);
    parent->registerFinishedAction(_movementFinishedAction);
}
void _backwardFunc(ActionHandler *parent, DataArgumentType arg)
{
    parent->getMovementAction()->backward(arg.distance, arg.speed);
    parent->registerLoopAction(_movementLoopAction);
    parent->registerFinishedAction(_movementFinishedAction);
}
void _turnFunc(ActionHandler *parent, DataArgumentType arg)
{
    parent->getMovementAction()->turn(arg.angle, arg.speed);
    parent->registerLoopAction(_movementLoopAction);
    parent->registerFinishedAction(_movementFinishedAction);
}
void _turnToFunc(ActionHandler *parent, DataArgumentType arg)
{
    parent->getMovementAction()->turnTo(arg.angle, arg.speed);
    parent->registerLoopAction(_movementLoopAction);
    parent->registerFinishedAction(_movementFinishedAction);
}
void _moveToFunc(ActionHandler *parent, DataArgumentType arg)
{
    parent->getMovementAction()->moveTo(arg.target, arg.speed);
    parent->registerLoopAction(_movementLoopAction);
    parent->registerFinishedAction(_movementFinishedAction);
}
void _delayFunc(ActionHandler *parent, DataArgumentType arg)
{
    parent->registerFinishedAction(_buzzerFinishedAction, std::to_string(millis() + arg.time));
}
void _buzzerFunc(ActionHandler *parent, DataArgumentType arg)
{
}
bool isActionTypesSetted=false;
void setupActionTypes()
{
    if (isActionTypesSetted)
        return;
    isActionTypesSetted = true;
    FORWARDAction = new ActionType(0, _forwardFunc);
    BACKWARDAction = new ActionType(0, _backwardFunc);
    TURNAction = new ActionType(0, _turnFunc);
    TURN_TOAction = new ActionType(0, _turnToFunc);
    MOVE_TOAction = new ActionType(0, _moveToFunc);
    DELAYAction = new ActionType(0, _delayFunc);
    BUZZERAction = new ActionType(0, _buzzerFunc);
    actionTypes = (std::map<std::string, ActionType *>){
        (std::pair<std::string, ActionType *>){"FORWARD", FORWARDAction},
        (std::pair<std::string, ActionType *>){"BACKWARD", BACKWARDAction},
        (std::pair<std::string, ActionType *>){"TURN", TURNAction},
        (std::pair<std::string, ActionType *>){"TURN_TO", TURN_TOAction},
        (std::pair<std::string, ActionType *>){"MOVE_TO", MOVE_TOAction},
        (std::pair<std::string, ActionType *>){"DELAY", DELAYAction},
        (std::pair<std::string, ActionType *>){"BUZZER", BUZZERAction}};
}
#endif