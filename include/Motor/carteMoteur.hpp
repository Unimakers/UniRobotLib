#pragma once
#include <Common/robotConfig.hpp>
#include <Common/communication.hpp>
#include <AccelStepper.h>

class CarteMoteur{
    AccelStepper left,right;
    RobotConfig config;
    CommunicationCarteExtension communication;
    Coord robotCoord;
    enum struct Etat_mvt
    {
        TURN_S,
        FORWARD,
        TURN_F,
        STILL
    };
    Etat_mvt etat_ec=Etat_mvt::STILL;
    Coord destination;
    int vitesse_mT;
    bool started = false;
    bool paused = false;
    public:
    CarteMoteur();
    void setup(RobotConfig config);
    void run();
    void loop();
    void setCoord(Coord coord);
    bool reachedTarget();
    void moveTo(Coord coord, int vitesse);
    bool moveToLoop();
    void forward(double distance, int vitesse);
    void backward(double distance, int vitesse);
    void turnTo(double angle, int vitesse);
    void turn(double angle, int vitesse);
    void debugPosition();
    void stop();
    void resume();
};