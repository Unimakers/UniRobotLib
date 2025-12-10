#include <Common/robotConfig.hpp>
#include <algorithm>
void RobotConfig::set(std::string name, std::string value)
{
    CustomDataConfigType c;
    c.type=TYPE::STRING;
    c.stringValue=value;
    this->set(name,c);
}
void RobotConfig::set(std::string name, int value)
{
    CustomDataConfigType c;
    c.type=TYPE::INT;
    c.intValue=value;
    this->set(name,c);
}
void RobotConfig::set(std::string name, double value)
{
    CustomDataConfigType c;
    c.type=TYPE::DOUBLE;
    c.doubleValue=value;
    this->set(name,c);
}
void RobotConfig::set(std::string name, CustomDataConfigType value)
{
    if(name=="robotType")this->robotType=value.intValue;
    else if(name=="robotWidth")this->robotWidth=value.intValue;
    else if(name=="wheel_spacing")this->wheel_spacing=value.intValue;
    else if(name=="wheel_size")this->wheel_size=value.intValue;
    else if(name=="step_multi")this->step_multi=value.intValue;
    else if(name=="step_rev_no_multi")this->step_rev_no_multi=value.intValue;
    else if(name=="dir_g")this->dir_g=value.intValue;
    else if(name=="dir_d")this->dir_d=value.intValue;
    else if(name=="step_g")this->step_g=value.intValue;
    else if(name=="step_d")this->step_d=value.intValue;
    else if(name=="en")this->en=value.intValue;
    else if(name=="acceleration")this->acceleration=value.intValue;
    else this->customConfig[name]=value;
    // auto calculate values
    this->step_rev=this->step_rev_no_multi*this->step_multi;
    this->step_cm=this->step_rev/(3.14159*(this->wheel_size/2));
}
CustomDataConfigType RobotConfig::get(std::string name)
{
    CustomDataConfigType c;
    c.type=TYPE::INT;
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    if(name=="robotType")c.intValue=this->robotType;
    else if(name=="robotWidth")c.intValue=this->robotWidth;
    else if(name=="wheel_spacing")c.intValue=this->wheel_spacing;
    else if(name=="wheel_size")c.intValue=this->wheel_size;
    else if(name=="step_multi")c.intValue=this->step_multi;
    else if(name=="step_rev_no_multi")c.intValue=this->step_rev_no_multi;
    else if(name=="dir_g")c.intValue=this->dir_g;
    else if(name=="dir_d")c.intValue=this->dir_d;
    else if(name=="step_g")c.intValue=this->step_g;
    else if(name=="step_d")c.intValue=this->step_d;
    else if(name=="en")c.intValue=this->en;
    else if(name=="acceleration")c.intValue=this->acceleration;
    else if (name=="lidar_rx")c.intValue=this->lidar_rx;
    else if (name=="lidar_tx")c.intValue=this->lidar_tx;
    else if (name=="lidar_pwm")c.intValue=this->lidar_pwm;
    else return this->customConfig[name];
    return c; // return the CustomDataConfigType
}