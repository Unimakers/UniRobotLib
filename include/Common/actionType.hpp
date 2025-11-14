#include <Common/actionHandler.hpp>
#include <map>
#include <string>
#include <functional>
#include <Common/coord.hpp>
// #include <any>
struct DataArgumentType{
    // common arguments
    int speed, distance, angle, time, tonality;
    Coord target;
    // custom arguments
    // std::map<std::string,std::any> customArguments;
};
class ActionType{
    /// @brief 0 is both, -1 is PAMI and 1 is ROBOT
    
    int compatibility;
    public:
    // std::function<void(ActionHandler*,DataArgumentType)> actionFunc;
    // ActionType(int compatibility, std::function<void(ActionHandler*,DataArgumentType)> actionFunc){
    //     this->compatibility=compatibility;
    //     this->actionFunc=actionFunc;
    // }
    // void action(ActionHandler* parent, DataArgumentType datas){
    //     this->actionFunc(parent,datas);
    // }
};
std::map<std::string,ActionType> actionTypes = {};