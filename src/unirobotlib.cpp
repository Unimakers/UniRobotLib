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
        this->carteLidar = new CarteLidar();
        break;
    case UniRobotLib_TypeDeCarte::CARTE_MOTEUR:
        this->carteMoteur = new CarteMoteur();
        break;
    case UniRobotLib_TypeDeCarte::CARTE_PRINCIPALE_PAMI:
        // init cartePrincipalePami Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_PRINCIPALE_ROBOT:
        this->cartePrincipaleRobot = new CartePrincipaleRobot();
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
        this->carteLidar->setup(config);
        break;
    case UniRobotLib_TypeDeCarte::CARTE_MOTEUR:
        this->carteMoteur->setup(config);
        break;
    case UniRobotLib_TypeDeCarte::CARTE_PRINCIPALE_PAMI:
        // setup cartePrincipalePami Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_PRINCIPALE_ROBOT:
        this->cartePrincipaleRobot->setup(config);
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
        this->carteLidar->loop();
        break;
    case UniRobotLib_TypeDeCarte::CARTE_MOTEUR:
        this->carteMoteur->loop();
        break;
    case UniRobotLib_TypeDeCarte::CARTE_PRINCIPALE_PAMI:
        // loop cartePrincipalePami Lib
        break;
    case UniRobotLib_TypeDeCarte::CARTE_PRINCIPALE_ROBOT:
        this->cartePrincipaleRobot->loop();
        break;
    default:
        // error
        break;
    }
}