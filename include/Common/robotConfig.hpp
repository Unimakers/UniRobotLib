#pragma once
#include <string>
#include <map>

class RobotConfig
{
    // defaults config {
    // -- high level related config {

    /// @brief 0 is both, -1 is PAMI, 1 is Robot, -2 is disabled
    int robotType;
    
    // -- }
    // -- hardware related config {
    // -- ++ physic hardware related config {

    /// @brief the extreme width of the robot
    int robotWidth;
    /// @brief the space between the lateral wheels (for a differential robot with 2 wheel)
    int wheel_spacing;
    /// @brief the wheel diameter (used for the step_cm value)
    int wheel_size;
    /// @brief the step multiplier (used for the step_cm value)
    int step_multi;
    /// @brief the amount of step per rev without multiplier (used for the step_cm value)
    int step_rev_no_multi;
    /// @brief the amount of step per rev, autoCalculated : step_rev_no_multi * step_multi
    int step_rev;
    /// @brief step per cm of the wheel, autoCalculated : step_rev / (2PI*(wheel_size/2))
    int step_cm;

    // -- ++ }
    // -- ++ pin hardware related config {
    // -- ++ -- driver pin hardware related config {

    /// @brief DIR gauche
    int dir_g;
    /// @brief DIR droite
    int dir_d;
    /// @brief STEP gauche
    int step_g;
    /// @brief STEP droite
    int step_d;
    /// @brief EN
    int en;

    // -- ++ --}
    // -- ++ -- 
    // -- ++ }
    // -- }


    // -- software related config {

    /// @brief the default acceleration used for the motors
    int acceleration;

    // -- }
    // }
    // custom config {

    /// @brief the custom configs keys and values
    std::map<std::string, std::string> customConfig;

    // }
};