#include <Motor/carteMoteur.hpp>
CarteMoteur::CarteMoteur(){}
void CarteMoteur::setup(RobotConfig config)
{
    this->config=config;
    this->communication=CommunicationCarteExtension();
    this->left = AccelStepper(AccelStepper::DRIVER,this->config.step_g,this->config.dir_g);
    this->right = AccelStepper(AccelStepper::DRIVER,this->config.step_d,this->config.dir_d);
}
void CarteMoteur::loop()
{
    this->communication.loop();
    CommunicationData ordre = this->communication.regarder();
    if(!started){
        if(ordre.action==CommAction::INIT_ROBOT)started=true;
        return;
    }
}
void CarteMoteur::run()
{
    left.run();
    right.run();
}

void CarteMoteur::setCoord(Coord coord){
    this->robotCoord=coord;
}
void CarteMoteur::moveTo(Coord coord, int vitesse){
    if(paused) return;
    turnTo(atan((coord.x - this->robotCoord.x) / (coord.y - this->robotCoord.y)), vitesse);
    this->etat_ec = Etat_mvt::TURN_S;
    this->destination = coord;
    this->vitesse_mT = vitesse;
}
bool CarteMoteur::moveToLoop(){}
bool CarteMoteur::reachedTarget(){}
void CarteMoteur::forward(double distance, int vitesse){}
void CarteMoteur::backward(double distance, int vitesse){}
void CarteMoteur::turnTo(double angle, int vitesse){}
void CarteMoteur::turn(double angle, int vitesse){}
void CarteMoteur::debugPosition(){}
void CarteMoteur::stop(){}
void CarteMoteur::resume(){}