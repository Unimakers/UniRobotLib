#pragma once
#include <Common/robotConfig.hpp>
#include <Common/actionHandler.hpp>
#include <Motor/carteMoteur.hpp>
class CartePrincipaleRobot{
    RobotConfig config;
    CommPrincipale communication;
    ActionHandler actionHandler;
    CarteMoteur carteMoteur;
    public:
    /// @brief init cartePrincipaleRobot
    CartePrincipaleRobot();
    void setup(RobotConfig config);
    void loop();
};