#pragma once
#include <Common/robotConfig.hpp>
#include <Common/communication_simplified.hpp>
#include <Common/coord.hpp>
#include <Motor/carteMoteur.hpp>
class MovementAction{
    /// @brief the robot configuration (to know if pami mode or main robot mode, and if pami mode to pass the config to the direct motors control class)
    RobotConfig config;
    /// @brief Communication to motor card if main robot mode
    CommPrincipale* communication;
    /// @brief Direct Motors control if pami robot mode
    CarteMoteur* carteMoteur;
    public:
    MovementAction();
    /// @brief Forward relative
    /// @param distance the distance (in cm)
    /// @param speed the speed (in cm/s)
    void forward(int distance, int speed);
    /// @brief Backward relative
    /// @param distance the distance (in cm)
    /// @param speed the speed (in cm/s)
    void backward(int distance, int speed){return forward(-distance,speed);}
    /// @brief Turn relative
    /// @param angle the angle (in degrees)
    /// @param speed the speed (in cm/s)
    void turn(double angle, int speed);
    /// @brief Turn To Absolute
    /// @param angle the angle (in degrees)
    /// @param speed the speed (in cm/s)
    void turnTo(double angle, int speed);
    /// @brief Move To absolute
    /// @param coord the position (x and y in cm and a in degrees)
    /// @param speed the speed (in cm/s)
    void moveTo(Coord coord, int speed);
};