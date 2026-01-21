/**
 * @file communication.hpp
 * 
 * @brief Librairie de communication, TEMPORAIREMENT MISE EN PAUSE POUR PLUS DE SIMPLICITÉ ET D'EFFICACITÉ
 * 
 * Bonjour futur développeur de cette librairie, cette librairie communication était une tentative de protocole de communication universel interne au robot
 * pour des raisons de temps et d'efficacité du code cette librairie est mise en pause, si tu trouves le temps et l'envie et / ou le besoin de faire fonctionner
 * cette librairie, n'hésite pas à essayer de continuer à la développer, tout a été codé pour être modelable, normalement, en espérant que cela puisse fonctionner un jour.
 */
#pragma once
// quand vous aurez complété cette librairie pensez à modifier THIS_LIB_IS_ENABLED pour mettre 1, ou alors à retirer le #if et le #end à la fin,
// mais en attendant pour des raisons de sécurité cette librairie est desactivée par cette variable
#define THIS_LIB_IS_ENABLED 0
#if THIS_LIB_IS_ENABLED==1
#include <Common/typeDeCarte.hpp>
#include <string>
#include <vector>
#include <map>
#include <SoftwareSerial.h>
#define COMMACTION_SIZE 13
enum struct IdCarte : int
{
    CARTE_PRINCIPALE = 0,
    CARTE_MOTEUR = 1,
    CARTE_LIDAR = 2,
    CARTE_IHM = 3,
    CARTE_EXTENSION_1 = 4,
    CARTE_EXTENSION_2 = 5,
    CARTE_EXTENSION_3 = 6
};

enum struct CommAction : int
{
    NONE = 0,                   // aucune action
    LIDAR_DETECTION = 1,        // détection par le lidar
    FORWARD = 2,                // avancer
    BACKWARD = 3,               // reculer
    TURN_LEFT = 4,              // tourner à gauche
    TURN_RIGHT = 5,             // tourner à droite
    TURN_TO_ANGLE = 6,          // tourner à un angle précis
    MOVE_TO_POSITION = 7,       // aller à une position précise
    CUSTOM_MOTOR_COMMAND = 8,   // commande moteur personnalisée
    IHM_ACTIVATED = 9,          // action déclenchée par l'IHM
    IHM_DEACTIVATED = 10,       // action désactivée par l'IHM
    IHM_UPDATE = 11,            // mise à jour de l'IHM
    LIDAR_POSITION_UPDATE = 12, // mise à jour de la position du lidar FINALEMENT ON NE FAIT PAS CETTE OPTION, 
    INIT_ROBOT = 13,            // activation des moteurs du lidar etc. activé au début de l'initialisation, mais pas au tout début non plus pour éviter de consommer avec les moteurs
    //ROUTE_DATA = 13           // routage de données entre cartes
};
enum struct COMM_PERSISTENCE : int
{
    ERASE_NEXT_LOOP = 0,        // effacer à la prochaine loop
    KEEP_UNTIL_NEXT_RECEIVE = 1 // garder jusqu'à la prochaine réception d'un meme type
};
struct CommunicationData
{
    COMM_PERSISTENCE persistence; // modifier type de donnée
    CommAction action;            // modifier type de donnée
    std::string argument;         // modifier type de donnée
    public:
    static std::string toString(CommunicationData data){
        return std::to_string(static_cast<int>(data.persistence)) + ":" + std::to_string(static_cast<int>(data.action)) + ":" + data.argument;
    }
    static CommunicationData fromString(std::string reception){
        CommunicationData commDataNone = {COMM_PERSISTENCE::ERASE_NEXT_LOOP, CommAction::NONE, ""};
        if (reception.empty())
        {
            return commDataNone;
        }
        CommunicationData receivedData;
        if (reception.find(":") == std::string::npos)
        {
            return commDataNone;
        }
        int receivedPersistence = (std::stoi(reception.substr(0, reception.find(":"))));
        if (receivedPersistence < 0 || receivedPersistence > 1)
        {
            return commDataNone;
        }
        receivedData.persistence = static_cast<COMM_PERSISTENCE>(receivedPersistence);
        if (reception.find(":") == std::string::npos)
        {
            return commDataNone;
        }
        reception = reception.substr(reception.find(":") + 1);
        int receivedAction = (std::stoi(reception.substr(0, reception.find(":"))));
        if (receivedAction < 0 || receivedAction > 12)
        {
            return commDataNone;
        }
        receivedData.action = static_cast<CommAction>(receivedAction);
        reception = reception.substr(reception.find(":") + 1);
        if (reception.empty())
        {
            return commDataNone;
        }
        receivedData.argument = reception;
        return receivedData;
    }
    // rajouter d'autres trucs
};
CommunicationData commDataNone = {COMM_PERSISTENCE::ERASE_NEXT_LOOP, CommAction::NONE, ""};
class CommunicationCartePrincipale
{
    std::map<IdCarte,EspSoftwareSerial::UART> serialMap;
    std::map<int,std::vector<CommunicationData>> toSend;
    std::map<int,std::vector<CommunicationData>> receivedBuffer;
    void _envoiSerial(int idCarte, std::string data);
    std::string _receiptSerial(int idCarte);
    short isReceiving=0;
    std::string receipt_en_cours="";
public:
    /// @brief initialisation protocole communication
    CommunicationCartePrincipale();
    /// @brief Permet d'envoyer les données à une carte
    /// @param idCarte Identifiant de la carte à laquelle envoyer les données
    /// @param  data Données à envoyer
    void envoyer(int idCarte, CommunicationData data);
    /// @brief appelé à chaque début de loop pour rien pour l'instant //pour recevoir les données et appelle la fonction routeur
    void loop();

    // /// @brief route les données reçues vers les différentes cartes intéressées si besoin, toutes données de carte extension passe obligatoirement par la carte
    // void routeur(); Au final pas sur que le routage soit vraiment important pour l'instant

    /// @brief Permet de regarder dans les données reçues les données envoyées par la carte X
    /// @param idCarte Identifiant de la carte dont on veut regarder les données
    /// @return Données sous forme \ref CommunicationData
    CommunicationData regarder(int idCarte);
    /// @brief Permet de regarder toutes les données reçues les données envoyées par la carte X
    /// @param idCarte Identifiant de la carte dont on veut regarder les données
    /// @return Vecteur de données sous forme std::vector< \ref CommunicationData >
    std::vector<CommunicationData> regarder_tout(int idCarte);
};
class CommunicationCarteExtension
{
public:
    /// @brief initialisation protocole communication
    CommunicationCarteExtension();
    /// @brief Permet d'envoyer des données à la carte principale
    /// @param  data Données à envoyer
    void envoyer(CommunicationData data);
    /// @brief appelé à chaque début de loop pour recevoir les données
    void loop();
    /// @brief récupère les données reçues
    /// @return données reçues
    CommunicationData regarder();
};
#endif