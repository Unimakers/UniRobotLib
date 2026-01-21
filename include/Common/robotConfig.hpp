#pragma once
#include <Common/customDataType.hpp>
#include <string>
#include <map>
#include <vector>
#include <Common/strategie.hpp>



/// @brief Robot Config
class RobotConfig
{
    public:
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
    /// @brief lidar rx
    int lidar_rx;
    /// @brief lidar tx
    int lidar_tx;
    /// @brief lidar pwm
    int lidar_pwm;
    /// @brief tirette pin
    int tirette_pin;
    /// @brief Rx de communication vers principal sur la carte moteur
    int carteMoteurCommRX;
    /// @brief Tx de communication vers principal sur la carte moteur
    int carteMoteurCommTX;
    /// @brief Rx de communication vers principal sur la carte lidar
    int carteLidarCommRX;
    /// @brief Tx de communication vers principal sur la carte lidar
    int carteLidarCommTX;
    /// @brief Rx de communication vers lidar sur la carte principale
    int mainToLidarRX;
    /// @brief Tx de communication vers lidar sur la carte principale
    int mainToLidarTX;
    /// @brief Rx de communication vers moteur sur la carte principale
    int mainToMotorRX;
    /// @brief Tx de communication vers moteur sur la carte principale
    int mainToMotorTX;

    // -- ++ --}
    // -- ++ -- 
    // -- ++ }
    // -- }


    // -- software related config {

    /// @brief the default acceleration used for the motors
    int acceleration;

    /// @brief robot strategy (only if main card of PAMI or ROBOT)
    Strategie strategie;
    /// @brief the robot initialisation strategy (only if main card of PAMI or ROBOT)
    Strategie initStrategie;

    // -- }
    // }
    // custom config {

    /// @brief the custom configs keys and values
    std::map<std::string, CustomDataConfigType> customConfig;


    // }

    /// @brief RobotConfig initialisation
    RobotConfig();
    
    // global setters and getters

    /// @brief setter for \p name with string \p value 
    /// @param name the name of the config element
    /// @param value the value of the config element as string
    void set(std::string name, std::string value);
    /// @brief setter for \p name with int \p value 
    /// @param name the name of the config element
    /// @param value the value of the config element as int
    void set(std::string name, int value);
    /// @brief setter for \p name with double \p value 
    /// @param name the name of the config element
    /// @param value the value of the config element as double
    void set(std::string name, double value);
    /// @brief setter for \p name with \ref CustomDataConfigType \p value
    /// @param name the name of the config element
    /// @param value the value of the config element as \ref CustomDataConfigType
    ///
    /// C'est vraiment \ref CustomDataConfigType qu'il faut utiliser pour les types complexes
    void set(std::string name, CustomDataConfigType value);
    /// @brief getter for the config element \p name
    /// @param name the name of the config element
    /// @return the value as \p CustomDataConfigType
    CustomDataConfigType get(std::string name);
};