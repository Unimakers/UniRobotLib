#pragma once
#include <Common/communication.hpp>
#include <Common/robotConfig.hpp>
#include <Common/actionHandler.hpp>

class CartePrincipaleRobot{
    RobotConfig config;
    CommunicationCartePrincipale communication;
    ActionHandler actionHandler;
    public:
    /// @brief init cartePrincipaleRobot
    CartePrincipaleRobot();
    void setup(RobotConfig config,Strategie strat);
    void loop();
};