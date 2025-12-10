#include <unirobotlib.hpp>
UniRobotLib::UniRobotLib(UniRobotLib_TypeDeCarte type_de_carte)
{
    this->type = type_de_carte;
    switch (type_de_carte)
    {
    case UniRobotLib_TypeDeCarte::CARTE_CONTROLE:
        // init carteControle Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_EXTENSION:
        // init carteExtension Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_LIDAR:
        this->carteLidar = CarteLidar();
        break;
    case UniRobotLib_TypeDeCarte::CARTE_MOTEUR:
        // init carteMoteur Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_PRINCIPALE_PAMI:
        // init cartePrincipalePami Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_PRINCIPALE_ROBOT:
        // init cartePrincipaleRobot Lib
        break;
    default:
        // error
        break;
    }
}
void UniRobotLib::setup(RobotConfig config)
{
    switch (this->type)
    {
    case UniRobotLib_TypeDeCarte::CARTE_CONTROLE:
        // setup carteControle Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_EXTENSION:
        // setup carteExtension Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_LIDAR:
        this->carteLidar.setup(config);
        break;
    case UniRobotLib_TypeDeCarte::CARTE_MOTEUR:
        // setup carteMoteur Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_PRINCIPALE_PAMI:
        // setup cartePrincipalePami Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_PRINCIPALE_ROBOT:
        // setup cartePrincipaleRobot Lib
        break;
    default:
        // error
        break;
    }
}
void UniRobotLib::loop()
{
    switch (this->type)
    {
    case UniRobotLib_TypeDeCarte::CARTE_CONTROLE:
        // loop carteControle Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_EXTENSION:
        // loop carteExtension Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_LIDAR:
        this->carteLidar.loop();
        break;
    case UniRobotLib_TypeDeCarte::CARTE_MOTEUR:
        // loop carteMoteur Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_PRINCIPALE_PAMI:
        // loop cartePrincipalePami Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_PRINCIPALE_ROBOT:
        // loop cartePrincipaleRobot Lib
        break;
    default:
        // error
        break;
    }
}