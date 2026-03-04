#pragma once
#include <Common/actionType.hpp>
#include <Common/actionHandler.hpp>
ActionType *FORWARDAction;
ActionType *BACKWARDAction;
ActionType *TURNAction;
ActionType *TURN_TOAction;
ActionType *MOVE_TOAction;
ActionType *DELAYAction;
ActionType *BUZZERAction;
bool isActionTypesSetted=false;
void setupActionTypes();
/// @brief predefined default actionTypes list
std::map<std::string,ActionType*> actionTypes= (std::map<std::string,ActionType*>){
    (std::pair<std::string,ActionType*>){"FORWARD",FORWARDAction},
    (std::pair<std::string,ActionType*>){"BACKWARD",BACKWARDAction},
    (std::pair<std::string,ActionType*>){"TURN",TURNAction},
    (std::pair<std::string,ActionType*>){"TURN_TO",TURN_TOAction},
    (std::pair<std::string,ActionType*>){"MOVE_TO",MOVE_TOAction},
    (std::pair<std::string,ActionType*>){"DELAY",DELAYAction},
    (std::pair<std::string,ActionType*>){"BUZZER",BUZZERAction}
};