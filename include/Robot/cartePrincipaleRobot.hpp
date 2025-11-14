#pragma once
#include <unirobotlib.hpp>

class CartePrincipaleRobot{
    UniRobotLib* parent;
    public:
    /// @brief init cartePrincipaleRobot
    CartePrincipaleRobot();
    void setup();
    void loop();
};