#include <Common/actionType.hpp>
#include <Common/actionHandler.hpp>
void ActionType::action(ActionHandler *parent, DataArgumentType datas)
{
    if (this->compatibility == -2)
        return;
    if (this->compatibility != 0 && parent->getConfigValue("robotType").intValue != this->compatibility)
        return;
    this->actionFunc(parent, datas);
}