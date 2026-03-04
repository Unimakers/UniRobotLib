#pragma once
#ifndef HELLO_WORLD_ACTDEF
#define HELLO_WORLD_ACTDEF
#include <Common/actionType.hpp>
extern ActionType *FORWARDAction;
extern ActionType *BACKWARDAction;
extern ActionType *TURNAction;
extern ActionType *TURN_TOAction;
extern ActionType *MOVE_TOAction;
extern ActionType *DELAYAction;
extern ActionType *BUZZERAction;
void setupActionTypes();
/// @brief predefined default actionTypes list
extern std::map<std::string,ActionType*> actionTypes;
#endif