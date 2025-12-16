#include <Robot/cartePrincipaleRobot.hpp>
CartePrincipaleRobot::CartePrincipaleRobot()
{
}
void CartePrincipaleRobot::setup(RobotConfig config)
{
    this->config = config;
    if(this->config.robotType==-2)return;
    config.set("robotType",1); // force robot type to robot
    this->communication = CommunicationCartePrincipale();
    this->actionHandler.setup(config,&this->communication);
}
void CartePrincipaleRobot::loop()
{
    if(this->config.robotType==-2)return;
    actionHandler.loop();
}