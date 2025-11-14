#pragma once
#include <Common/typeDeCarte.hpp>
#include <Lidar/cartelidar.hpp>
class UniRobotLib{
    UniRobotLib_TypeDeCarte type;
    CarteLidar carteLidar;
    public:
    UniRobotLib(UniRobotLib_TypeDeCarte);
    void setup(); // appelle le "setup" de la carte actuelle
    void loop(); // appelle le "loop" de la carte actuelle
};