#include <Motor/carteMoteur.hpp>
CarteMoteur::CarteMoteur() {}
void CarteMoteur::setup(RobotConfig config)
{
    this->config = config;
    this->communication = CommunicationCarteExtension();
    this->left = AccelStepper(AccelStepper::DRIVER, this->config.step_g, this->config.dir_g);
    this->right = AccelStepper(AccelStepper::DRIVER, this->config.step_d, this->config.dir_d);
}
DataArgumentType cutArguments(std::string argument)
{
    DataArgumentType t;
    std::string arg = argument;
    int noName = 0;
    while (arg.find("&") != std::string::npos)
    {
        std::string curarg = arg.substr(0, arg.find("&"));
        if (curarg.find("=") == std::string::npos)
        {
            t.customArguments[std::to_string(noName)] = curarg;
            noName++;
        }
        else
        {
            std::string name = curarg.substr(0, curarg.find("="));
            std::string val = curarg.substr(curarg.find("=") + 1);
            if (name == "C")
            {
                std::string vv = val;
                if (vv.find(",") != std::string::npos)
                {
                    t.target.x = std::stod(vv.substr(0, vv.find(",")));
                    vv = vv.substr(vv.find(",") + 1);
                    if (vv.find(",") != std::string::npos)
                    {
                        t.target.y = std::stod(vv.substr(0, vv.find(",")));
                        vv = vv.substr(vv.find(",") + 1);
                        if (vv.find(",") != std::string::npos)
                        {
                            t.target.a = std::stod(vv.substr(0, vv.find(",")));
                            vv = vv.substr(vv.find(",") + 1);
                        }
                    }
                }
            }
            else if (name == "s")
            {
                t.speed = std::stoi(val);
            }
            else if (name == "d")
            {
                t.distance = std::stoi(val);
            }
            else if (name == "a")
            {
                t.angle = std::stoi(val);
            }
            else
            {
                t.customArguments[name] = val;
            }
        }
        arg = arg.substr(arg.find("&") + 1);
    }
    return t;
}
void CarteMoteur::loop()
{
    this->communication.loop();
    CommunicationData ordre = this->communication.regarder();
    if (!this->started)
    {
        if (ordre.action == CommAction::INIT_ROBOT)
            this->started = true;
        return;
    }
    DataArgumentType a = cutArguments(ordre.argument);
    bool lidar = false;
    switch (ordre.action)
    {
    case CommAction::FORWARD:
        forward(a.distance,a.speed);
        break;
    case CommAction::BACKWARD:
        backward(a.distance,a.speed);
        break;
    case CommAction::MOVE_TO_POSITION:
        moveTo(a.target,a.speed);
        break;
    case CommAction::TURN_LEFT:
        turn(-a.angle,a.speed);
        break;
    case CommAction::TURN_RIGHT:
        turn(a.angle,a.speed);
        break;
    case CommAction::TURN_TO_ANGLE:
        turnTo(a.angle,a.speed);
        break;
    case CommAction::LIDAR_DETECTION:
        lidar = true;
        break;
    case CommAction::CUSTOM_MOTOR_COMMAND:
        // custom(leftAction, rightAction);
        break;
    }
}
void CarteMoteur::run(bool *lidar)
{
    // if(*lidar && pamimode) return;
    if (*lidar)
    {
        stop();
    }
    else if (this->paused)
    {
        resume();
    }
    this->left.run();
    this->right.run();
}

void CarteMoteur::setCoord(Coord coord)
{
    this->robotCoord = coord;
}
void CarteMoteur::moveTo(Coord coord, int vitesse)
{
    if (this->paused)
        return;
    turnTo(atan((coord.x - this->robotCoord.x) / (coord.y - this->robotCoord.y)), vitesse);
    this->etat_ec = Etat_mvt::TURN_S;
    this->destination = coord;
    this->vitesse_mT = vitesse;
}
bool CarteMoteur::moveToLoop()
{
    if (this->paused)
        return false;
    if (this->etat_ec == Etat_mvt::TURN_S)
    {
        this->etat_ec = Etat_mvt::FORWARD;
        float d = sqrt(pow((this->destination.x - this->robotCoord.x), 2) + pow((this->destination.y - this->robotCoord.y), 2));
        forward(d, this->vitesse_mT);
        return false;
    }
    else if (this->etat_ec == Etat_mvt::FORWARD)
    {
        this->etat_ec = Etat_mvt::TURN_F;
        turnTo(this->destination.a, this->vitesse_mT);
        return false;
    }
    else
    {
        this->etat_ec = Etat_mvt::STILL;
        return true;
    }
}
bool CarteMoteur::reachedTarget()
{
    if (this->paused)
        return false;
    if (not bool(bool(this->right.distanceToGo()) + bool(this->left.distanceToGo())))
    {
        if (this->etat_ec != Etat_mvt::STILL)
        {
            return moveToLoop();
        }
        this->currentaction.left = 0;
        this->currentaction.right = 0;
        return true;
    }
    return false;
}
void CarteMoteur::forward(double distance, int vitesse)
{
    if (this->paused)
        return;
    // sendCurrentAngle({0, Math::signum(distance)});
    int nbr_step = distance * this->config.step_cm;
    this->right.setAcceleration(vitesse / 2);
    this->right.setMaxSpeed(vitesse);
    this->right.move(ceil(distance * this->config.step_cm));

    this->left.setAcceleration(vitesse / 2);
    this->left.setMaxSpeed(vitesse);
    this->left.move(ceil(distance * this->config.step_cm));
    // debugPrint("set max speed");
    // debugPrintln(vitesse);

    this->robotCoord.x += distance * sin(this->robotCoord.a);
    this->robotCoord.y += distance * cos(this->robotCoord.a);
}
void CarteMoteur::backward(double distance, int vitesse)
{
    forward(-distance, vitesse);
}
void CarteMoteur::turnTo(double angle, int vitesse)
{
    if (this->paused)
        return;
    int angle_rel = this->robotCoord.a - angle;
    if (angle_rel > 180)
    {
        turn(180 - angle_rel, vitesse);
    }
    else
    {
        turn(angle_rel, vitesse);
    }
}
void CarteMoteur::turn(double angle, int vitesse)
{
    if (this->paused)
        return;
    // sendCurrentAngle({Math::signum(angle) * 0.5, 0.5});
    this->right.setAcceleration(vitesse / 2);
    this->right.setMaxSpeed(vitesse);

    this->left.setAcceleration(vitesse / 2);
    this->left.setMaxSpeed(vitesse);

    int nbr_step = (this->config.wheel_spacing / 2) * (angle * PI / 180);
    this->right.move(-nbr_step * this->config.step_cm);
    this->left.move(nbr_step * this->config.step_cm);

    this->robotCoord.a += angle;
}
void CarteMoteur::debugPosition()
{
}
void CarteMoteur::stop()
{
    if (this->paused)
        return;
    this->currentaction.left = this->left.distanceToGo();
    this->currentaction.right = this->right.distanceToGo();
    /*if(pamimode){
        this->right.setAcceleration(4000/2);
        this->left.setAcceleration(4000/2);
        this->right.setMaxSpeed(4000);
        this->left.setMaxSpeed(4000);
    }*/
    this->right.stop();
    this->left.stop();
    delay(20);
    this->currentaction.left -= this->left.distanceToGo();
    this->currentaction.right -= this->right.distanceToGo();
    // delay(2000);
    this->paused = true;
}
void CarteMoteur::resume()
{
    if (!this->paused)
        return;
    this->paused = false;
    this->right.move(this->currentaction.right);
    this->left.move(this->currentaction.left);
}