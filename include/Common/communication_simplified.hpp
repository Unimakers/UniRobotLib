#pragma once
#include <string>
#include <vector>
#include <map>
#include <SoftwareSerial.h>

enum struct CommAction : char
{
    NONE = 'N',                   // aucune action
    FORWARD = 'F',                // avancer
    BACKWARD = 'B',               // reculer
    TURN_LEFT = 'L',              // tourner à gauche
    TURN_RIGHT = 'R',             // tourner à droite
    TURN_TO_ANGLE = 'A',          // tourner à un angle précis
    MOVE_TO_POSITION = 'M',       // aller à une position précise
    CUSTOM_MOTOR_COMMAND = 'C',   // commande moteur personnalisée
    INIT_ROBOT = 'I',             // activation des moteurs du lidar etc. activé au début de l'initialisation, mais pas au tout début non plus pour éviter de consommer avec les moteurs
    LIDAR_DETECTION = 'S',        // pour indiquer à la carte moteur qu'il y a eu une detection de lidar
    NO_NEW_DATA = 'Z'             // permet d'avoir un return quand la reception n'est pas finie ou qu'il n'y a vraiment pas de donnée qui a encore été reçue (uniquement utile pour carte moteur ducoup)
};
// char CANCEL_CURRENT = '$';
#define CANCEL_CURRENT '$'
// char END_OF_COMM = '@';
#define END_OF_COMM '@'
class CommPrincipale
{
    /*the buffer of the action to Send to the motor, we write one byte per loop, 
    we finish with CANCEL_CURRENT, while the motor card don't receive CANCEL_CURRENT, 
    it continues to append to a reception variable, if we want to stop the current send then
    we send the END_OF_COMM variable, the slave card will erase the current reception variable*/
    bool isSendingToMotor=false;
    std::string motorToSend="";
    int motorToSendIndex=0;
    /*there is no "lidarToSend" variable or "sendToLidar" function cause we don't send anything to lidar,
    we just receive state, and if we are running then we will take care of this state,
    else we just have to don't care, that's all*/
    EspSoftwareSerial::UART lidarComm;
    EspSoftwareSerial::UART motorComm;
    // we store lidar state and motor state so we receive at the start of the loop and we can read at any moment of the loop without interfering
    bool lidarState;
    bool motorState;
    public:
    CommPrincipale(){};
    void setup(int RxCommLidar, int TxCommLidar, int RxCommMoteur, int TxCommMoteur);
    /// @brief  Get the lidar state
    /// @return 0 if nothing, 1 if lidar detected something
    bool getLidarState();
    /// @brief Send action to motor
    /// @param action the action
    /// @param arguments the arguments (parsed from the actionHandler code)
    void sendActionToMotor(CommAction action, std::string arguments);
    /// @brief Get the motor state
    /// @return 0 if running, 1 if finished movement
    bool getMotorState();
    void loop();
};
class CommEsclave{
    EspSoftwareSerial::UART mainComm;
    std::string currentReception = "";
    bool finishedReception = false;
    CommAction receivedAction = CommAction::NO_NEW_DATA;
    std::string receivedArguments="";
    bool stateToSend=false;
    public:
    CommEsclave(){};
    void setup(int rxComm, int txComm);
    /// @brief Send state (detection if lidar, action finished if motor)
    /// @param value 0 or 1
    void sendState(bool value);
    CommAction getAction();
    std::string getArgs();
    void loop();
};
