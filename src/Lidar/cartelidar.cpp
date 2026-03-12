#include <Lidar/cartelidar.hpp>


HardwareSerial serialLidar(0);
void CarteLidar::setup(RobotConfig config)
{
    this->robotConfig = config;
    int rx = this->robotConfig.get("lidar_rx").intValue;
    int tx = this->robotConfig.get("lidar_tx").intValue;
    pinMode(this->robotConfig.lidar_pwm, OUTPUT);
    analogWrite(this->robotConfig.get("lidar_pwm").intValue, 160);
    this->lidar.begin(serialLidar, rx, tx);
    this->lidar.startScan();
}
void CarteLidar::loop(bool debug)
{
    communication.loop();
    LidarPoint lp = this->detect();
    CommAction receivedAction = communication.getAction();
    if(lp.isPoint)
    {
        //POUR l'instant on ne fait pas d'envoi de position mais uniquement de l'envoi de 1 si obstacle, 0 si rien
        // Coord pointCoord = this->localizePoint(lp);
        // SendedPoint sp;
        // sp.x = pointCoord.x;
        // sp.y = pointCoord.y;
        // sp.a = pointCoord.a;
        // sp.quality = lp.quality;
        // sp.isObstacle = lp.obstacle;
        // CommunicationData data;
        // data.persistence = COMM_PERSISTENCE::ERASE_NEXT_LOOP;
        // data.action = CommAction::LIDAR_DETECTION;
        // data.argument = std::to_string(sp.x) + "," + std::to_string(sp.y) + "," + std::to_string(sp.a) + "," + std::to_string(sp.quality) + "," + std::to_string(sp.isObstacle);
        // this->communication.envoyer(data);
        double xPoint = cos(lp.angle) * lp.distance;
        double yPoint = sin(lp.angle) * lp.distance;
        Serial.println(((std::string) ">point:" + std::to_string(xPoint) + ":" + std::to_string(yPoint) + "|xy").c_str());
    }
    if(lp.obstacle){
        this->hasObstacle=true;
    }
    communication.sendState(this->hasObstacle);
}
CarteLidar::LidarPoint CarteLidar::detect()
{
    LidarPoint lp;
    if(IS_OK(lidar.waitPoint()))
    {
        RPLidarMeasurement m = lidar.getCurrentPoint();
        lp.isPoint = true;
        lp.angle = m.angle;
        lp.distance = (float)m.distance / 1000.0; // convert mm to m
        lp.quality = m.quality;
        if(m.distance < 0.4 && m.distance > 0.1) lp.obstacle = true;
    }
    else
    {
        analogWrite(this->robotConfig.get("lidar_pwm").intValue, 0);
        rplidar_response_device_info_t info;
        if (IS_OK(lidar.getDeviceInfo(info, 100)))
        {
            // detected...
            lidar.startScan();
            analogWrite(this->robotConfig.get("lidar_pwm").intValue, 160);
            delay(1000);
        }
        else;
    }
    return lp;
}
Coord CarteLidar::localizePoint(LidarPoint lp)
{
    Coord coord;
    coord.a = coordRobot.a + lp.angle;
    coord.x = coordRobot.x + lp.distance * cos(coord.a);
    coord.y = coordRobot.y + lp.distance * sin(coord.a);
    return coord;
}
