#pragma once
enum struct UniRobotLib_TypeDeCarte{
    CARTE_PRINCIPALE_ROBOT, // Carte principale du robot (uniquement communication vers autres cartes)
    CARTE_MOTEUR, // Carte de controle des moteurs du robot (reçoit communications de la carte principale et renvoie par exemple l'endroit sur lequel s'arrêtent les roues)
    CARTE_LIDAR, // Carte du lidar (reçoit les instructions comme la position d'arret du moteur etc. et renvoit une position approximative par rapport aux balises et également la position des ennemis)
    CARTE_CONTROLE, // Carte IHM (envoie communication etat boutons et reçoit inforation à afficher sur écrans)
    CARTE_EXTENSION, // Carte extension
    CARTE_PRINCIPALE_PAMI, // Carte principale du PAMI (est indépendante, n'a pas de carte externe)
};