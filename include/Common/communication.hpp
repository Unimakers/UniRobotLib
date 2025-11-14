#include <Common/typeDeCarte.hpp>
struct CommunicationData{
        int type; // modifier type de donnée
        int message; // modifier type de donnée
        // rajouter d'autres trucs
    };
class CommunicationCartePrincpale{
    public:
    /// @brief initialisation protocole communication
    CommunicationCartePrincpale();
    // documentation dans communication.cpp, fonction permet d'envoyer des données à une carte
    void envoyer(int,CommunicationData);
    /// @brief appelé à chaque début de loop pour recevoir les données et appelle la fonction routeur
    void loop();
    /// @brief route les données reçues vers les différentes cartes intéressées si besoin, toutes données de carte extension passe obligatoirement par la carte
    void routeur();
    // commentaire dans communication.cpp, fonction permet de regarder dans les données reçues les données envoyées par la carte X
    CommunicationData regarder(int);
};
class CommunicationCarteExtension{
    public:
    CommunicationCarteExtension();
    // commentaire dans communication.cpp, permet d'envoyer des données à la carte principale
    void envoyer(CommunicationData);
    /// @brief appelé à chaque début de loop pour recevoir les données
    void loop();
    /// @brief récupère les données reçues
    /// @return données reçues
    CommunicationData regarder();
};