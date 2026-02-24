#pragma once
#include <Common/actionType.hpp>
// void _forwardFunc(ActionHandler*parent,DataArgumentType arg){
    
// }
/// @brief predefined default actionTypes list
extern std::map<std::string,ActionType> actionTypes;
//  = (std::map<std::string,ActionType>){
//     (std::pair<std::string,ActionType>){"FORWARD",ActionType(0,_forwardFunc)}
// };