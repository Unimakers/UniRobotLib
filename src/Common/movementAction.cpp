#include <Common/movementAction.hpp>
MovementAction::MovementAction(RobotConfig conf, CommPrincipale *comm)
{
    this->config = conf;
    this->communication = comm;
    if(this->config.robotType==-1){
        this->carteMoteur = new CarteMoteur();
        this->carteMoteur->setup(this->config);
    }
}
void MovementAction::forward(double distance, int speed)
{
    if (this->config.robotType == -1)
    {
        // PAMI MODE
        this->carteMoteur->forward(distance, speed);
    }
    else if (this->config.robotType == 1)
    {
        this->communication->sendActionToMotor(CommAction::FORWARD, ("d=" + std::to_string(distance) + "&s=" + std::to_string(speed)));
    }
}
void MovementAction::turn(double angle, int speed)
{
    if (this->config.robotType == -1)
    {
        // PAMI MODE
        this->carteMoteur->turn(angle, speed);
    }
    else if (this->config.robotType == 1)
    {
        this->communication->sendActionToMotor(CommAction::TURN_RIGHT, ("a=" + std::to_string(angle) + "&s=" + std::to_string(speed)));
    }
}
void MovementAction::turnTo(double angle, int speed)
{
    if (this->config.robotType == -1)
    {
        // PAMI MODE
        this->carteMoteur->turnTo(angle, speed);
    }
    else if (this->config.robotType == 1)
    {
        this->communication->sendActionToMotor(CommAction::TURN_TO_ANGLE, ("a=" + std::to_string(angle) + "&s=" + std::to_string(speed)));
    }
}
void MovementAction::moveTo(Coord coord, int speed)
{
    if (this->config.robotType == -1)
    {
        // PAMI MODE
        this->carteMoteur->moveTo(coord, speed);
    }
    else if (this->config.robotType == 1)
    {
        this->communication->sendActionToMotor(CommAction::MOVE_TO_POSITION, (
                                                                                "C=" + std::to_string(coord.x) + "," + std::to_string(coord.y) + "," + std::to_string(coord.a) + "&s=" + std::to_string(speed)));
    }
}
void MovementAction::run(){
    if(this->config.robotType==-1){
        this->carteMoteur->loop();
    }
}
bool MovementAction::getStatus()
{
    if (this->config.robotType == -1)
    {
        // PAMI MODE
        return this->carteMoteur->reachedTarget();
    }
    else if (this->config.robotType == 1)
    {
        return this->communication->getMotorState();
    }
    return false;
}