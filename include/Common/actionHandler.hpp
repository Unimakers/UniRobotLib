#pragma once
#include <Common/communication.hpp>
#include <Common/robotConfig.hpp>
/** 
 * @brief Code de fonctionnement des actions, c'est ce code qui va faire fonctionner les stratégies, 
 * il s'agit donc du code "principal" dans le code de la carte principale du Robot et dans la carte du Pami.
 */
class ActionHandler{
    
    /**
     * @brief Le type d'état, il s'agit d'un type ne pouvant contenir que **4** valeurs: IDLE, RUNNING, PAUSED, FINISHED.
     * Ce type permet de définir des variables indiquant l'état de la stratégie.
     */
    enum struct STATE{
        /// @brief L'état IDLE : le robot a fini la précédente action et attend donc de passer à la prochaine action
        IDLE,
        /// @brief L'état RUNNING : le robot est entrain de faire fonctionner une action
        RUNNING,
        /// @brief L'état PAUSED : le robot est en pause pour une quelconque raison
        PAUSED,
        /// @brief L'état FINISHED : le robot a fini la stratégie en cours
        FINISHED
    };
    /**
     * @brief Le type de stratégie actuelle, il s'agit d'un type ne pouvant contenir que **2** valeurs
     */
    enum struct CURRENT_STRAT{
        INIT,RUN
    };
    STATE state = STATE::IDLE;
    CURRENT_STRAT curStrat = CURRENT_STRAT::INIT;
    RobotConfig config;
    CommunicationCartePrincipale* communication=nullptr;
    Strategie strategie,initStrategie;
    int currentActionIndex=0;
    public:
    ActionHandler();
    void setup(RobotConfig config,CommunicationCartePrincipale* communication);
    bool checkActionFinished();
    void nextAction();
    void loop();
    STATE getState(){return this->state;}
    void setState(STATE newState){this->state=newState;}
    CustomDataConfigType getConfigValue(std::string name){return this->config.get(name);}
    void setConfigValue(std::string name, CustomDataConfigType value){this->config.set(name,value);}
};