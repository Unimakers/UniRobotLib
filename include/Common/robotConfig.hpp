#pragma once
#include <Common/customDataType.hpp>
#include <string>
#include <map>
#include <vector>
#include <Common/strategie.hpp>

#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H
constexpr double PI_VAL = 3.14159;
/// @brief Robot Config
class RobotConfig
{
    public:
    // defaults config {
    // -- high level related config {

    /// @brief 0 is both, -1 is PAMI, 1 is Robot, -2 is disabled
    ValType<int> robotType;
    
    // -- }
    // -- hardware related config {
    // -- ++ physic hardware related config {

    /// @brief the extreme width of the robot
    ValType<int> robotWidth;
    /// @brief the space between the lateral wheels (for a differential robot with 2 wheel)
    ValType<int> wheel_spacing;
    /// @brief the wheel diameter (used for the step_cm value)
    ValType<int> wheel_size;
    /// @brief the step multiplier (used for the step_cm value)
    ValType<int> step_multi;
    /// @brief the amount of step per rev without multiplier (used for the step_cm value)
    ValType<int> step_rev_no_multi;
    /// @brief the amount of step per rev, autoCalculated : step_rev_no_multi * step_multi
    ValType<int,true,true> step_rev;
    /// @brief step per cm of the wheel, autoCalculated : step_rev / (2PI*(wheel_size/2))
    ValType<int,true,true> step_cm;

    // -- ++ }
    // -- ++ pin hardware related config {
    // -- ++ -- driver pin hardware related config {

    /// @brief DIR gauche
    ValType<int> dir_g;
    /// @brief DIR droite
    ValType<int> dir_d;
    /// @brief STEP gauche
    ValType<int> step_g;
    /// @brief STEP droite
    ValType<int> step_d;
    /// @brief EN
    ValType<int> en;
    /// @brief lidar rx
    ValType<int> lidar_rx;
    /// @brief lidar tx
    ValType<int> lidar_tx;
    /// @brief lidar pwm
    ValType<int> lidar_pwm;
    /// @brief tirette pin
    ValType<int> tirette_pin;
    /// @brief Rx de communication vers principal sur la carte moteur
    ValType<int> carteMoteurCommRX;
    /// @brief Tx de communication vers principal sur la carte moteur
    ValType<int> carteMoteurCommTX;
    /// @brief Rx de communication vers principal sur la carte lidar
    ValType<int> carteLidarCommRX;
    /// @brief Tx de communication vers principal sur la carte lidar
    ValType<int> carteLidarCommTX;
    /// @brief Rx de communication vers lidar sur la carte principale
    ValType<int> mainToLidarRX;
    /// @brief Tx de communication vers lidar sur la carte principale
    ValType<int> mainToLidarTX;
    /// @brief Rx de communication vers moteur sur la carte principale
    ValType<int> mainToMotorRX;
    /// @brief Tx de communication vers moteur sur la carte principale
    ValType<int> mainToMotorTX;

    // -- ++ --}
    // -- ++ -- 
    // -- ++ }
    // -- }


    // -- software related config {

    /// @brief the default acceleration used for the motors
    ValType<int> acceleration;

    /// @brief robot strategy (only if main card of PAMI or ROBOT)
    ValType<Strategie> strategie;
    /// @brief the robot initialisation strategy (only if main card of PAMI or ROBOT)
    ValType<Strategie> initStrategie;

    // -- }
    // }
    // custom config {

    /// @brief the custom configs keys and values
    ValType<std::map<std::string, CustomDataConfigType>> customConfig;


    // }

    /// @brief RobotConfig initialisation
    RobotConfig(){};
    
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
    void setLocked(bool locked){
        this->acceleration.setLocked(locked);
        this->carteLidarCommRX.setLocked(locked);
        this->carteLidarCommTX.setLocked(locked);
        this->carteLidarCommTX.setLocked(locked);
        this->carteMoteurCommRX.setLocked(locked);
        this->carteMoteurCommTX.setLocked(locked);
        this->customConfig.setLocked(locked);
        this->dir_d.setLocked(locked);
        this->dir_g.setLocked(locked);
        this->en.setLocked(locked);
        this->initStrategie.setLocked(locked);
        this->lidar_pwm.setLocked(locked);
        this->lidar_rx.setLocked(locked);
        this->lidar_tx.setLocked(locked);
        this->mainToLidarRX.setLocked(locked);
        this->mainToLidarTX.setLocked(locked);
        this->mainToMotorRX.setLocked(locked);
        this->mainToMotorTX.setLocked(locked);
        this->robotType.setLocked(locked);
        this->robotWidth.setLocked(locked);
        this->step_cm.setLocked(locked); // autoCalculated, lockedLocked is defined to True so it will not be editable except with securSetValue
        this->step_d.setLocked(locked);
        this->step_g.setLocked(locked);
        this->step_multi.setLocked(locked);
        this->step_rev.setLocked(locked); // autoCalculated, lockedLocked is defined to True so it will not be editable except with securSetValue
        this->step_rev_no_multi.setLocked(locked);
        this->strategie.setLocked(locked);
        this->tirette_pin.setLocked(locked);
        this->wheel_size.setLocked(locked);
        this->wheel_spacing.setLocked(locked);
    };
    void updateCalculs(){
        // for all autoCalculated values
        this->step_rev.securSetValue(this->step_rev_no_multi*this->step_multi,true);
        this->step_cm.securSetValue(this->step_rev / (2*PI_VAL*(wheel_size/2)),true);
    }
};
#endif