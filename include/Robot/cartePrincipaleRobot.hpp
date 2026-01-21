#pragma once
#include <Common/communication.hpp>
#include <Common/communication_simplified.hpp>
#include <Common/robotConfig.hpp>
#include <Common/actionHandler.hpp>

class CartePrincipaleRobot{
    RobotConfig config;
    CommPrincipale communication;
    ActionHandler actionHandler;
    public:
    /// @brief init cartePrincipaleRobot
    CartePrincipaleRobot();
    void setup(RobotConfig config);
    void loop();
};