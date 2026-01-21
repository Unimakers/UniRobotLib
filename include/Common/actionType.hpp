#pragma once
class ActionHandler;
//#include <Common/actionHandler.hpp>
#include <map>
#include <string>
#include <functional>
#include <Common/coord.hpp>
/// @brief arguments for the action
struct DataArgumentType{
    // --common arguments--

    /// @brief speed common argument
    int speed;
    /// @brief distance common argument
    int distance;
    /// @brief angle common argument
    int angle;
    /// @brief time common argument
    int time;
    /// @brief tonality common argument
    int tonality;
    /// @brief target common argument
    Coord target;
    
    // --map for custom arguments--

    /// @brief map of name : value, with value of any type converted to String to be reconverted to type in the fonction
    std::map<std::string,std::string> customArguments;
};
/// @brief ActionType
class ActionType{
    /// @brief 0 is both, -1 is PAMI and 1 is ROBOT, -2 mean disabled
    int compatibility;
    /// @brief actionFunc
    std::function<void(ActionHandler*,DataArgumentType)> actionFunc;
    public:
    /// @brief init ActionType
    /// @param compatibility 0 is both, -1 is PAMI, 1 is ROBOT, -2 mean disabled
    /// @param actionFunc the function of the action
    ActionType(int compatibility, std::function<void(ActionHandler*,DataArgumentType)> actionFunc){
        if(compatibility<-2 || compatibility > 1) compatibility=0;
        this->compatibility=compatibility;
        this->actionFunc=actionFunc;
    }
    ActionType(){
        this->compatibility=-2;
    };
    /// @brief call the function of the action
    /// @param parent the ActionHandler* parent class
    /// @param datas the arguments
    void action(ActionHandler* parent, DataArgumentType datas){
        if(this->compatibility==-2) return;
        this->actionFunc(parent,datas);
    }
};

/// @brief predefined default actionTypes list
std::map<std::string,ActionType> actionTypes = {};
