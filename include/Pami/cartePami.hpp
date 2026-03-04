#pragma once
#include <Common/robotConfig.hpp>
#include <Common/actionHandler.hpp>
#include <Motor/carteMoteur.hpp>
class CartePrincipalePami{
    RobotConfig config;
    ActionHandler actionHandler;
    CarteMoteur carteMoteur;
    public:
    /// @brief init cartePrincipalePami
    CartePrincipalePami();
    void setup(RobotConfig config);
    void loop();
};