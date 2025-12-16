#pragma once
#include <Common/typeDeCarte.hpp>
#include <Lidar/cartelidar.hpp>
#include <Robot/cartePrincipaleRobot.hpp>
#include <Motor/carteMoteur.hpp>
class UniRobotLib{
    UniRobotLib_TypeDeCarte type;
    CarteLidar carteLidar;
    CarteMoteur carteMoteur;
    CartePrincipaleRobot cartePrincipaleRobot;
    public:
    UniRobotLib(UniRobotLib_TypeDeCarte);
    void setup(RobotConfig config); // appelle le "setup" de la carte actuelle
    void loop(); // appelle le "loop" de la carte actuelle
};