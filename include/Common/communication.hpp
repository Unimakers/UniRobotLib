#pragma once
#include <Common/typeDeCarte.hpp>
#include <string>
#include <vector>
#include <map>
#include <SoftwareSerial.h>

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
    NONE = 0,                  // aucune action
    LIDAR_DETECTION = 1,       // détection par le lidar
    FORWARD = 2,               // avancer
    BACKWARD = 3,              // reculer
    TURN_LEFT = 4,             // tourner à gauche
    TURN_RIGHT = 5,            // tourner à droite
    TURN_TO_ANGLE = 6,         // tourner à un angle précis
    MOVE_TO_POSITION = 7,      // aller à une position précise
    CUSTOM_MOTOR_COMMAND = 8,  // commande moteur personnalisée
    IHM_ACTIVATED = 9,        // action déclenchée par l'IHM
    IHM_DEACTIVATED = 10,      // action désactivée par l'IHM
    IHM_UPDATE = 11,           // mise à jour de l'IHM
    LIDAR_POSITION_UPDATE = 12, // mise à jour de la position du lidar
    //ROUTE_DATA = 13            // routage de données entre cartes
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
    // rajouter d'autres trucs
};
CommunicationData commDataNone = {COMM_PERSISTENCE::ERASE_NEXT_LOOP, CommAction::NONE, ""};
class CommunicationCartePrincipale
{
    std::map<int,std::vector<CommunicationData>> toSend;
    std::map<int,std::vector<CommunicationData>> receivedBuffer;

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