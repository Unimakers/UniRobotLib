#include <Lidar/cartelidar.hpp>
#include <unirobotlib.hpp>
CarteLidar::CarteLidar()
{
}
HardwareSerial serialLidar(0);
void CarteLidar::setup(RobotConfig config)
{
    this->robotConfig = config;
    int rx = this->robotConfig.get("lidar_rx").intValue;
    int tx = this->robotConfig.get("lidar_tx").intValue;
    this->lidar.begin(serialLidar, rx, tx);
    analogWrite(this->robotConfig.get("lidar_pwm").intValue, 160);
}
void CarteLidar::loop()
{
    communication.loop();
    LidarPoint lp = this->detect();
    CommunicationData receiptData;
    receiptData = this->communication.regarder();
    if(receiptData.action == CommAction::LIDAR_POSITION_UPDATE)
    {
        // parse data
        std::string arg = receiptData.argument;
        size_t pos1 = arg.find(",");
        size_t pos2 = arg.find(",", pos1 + 1);
        size_t pos3 = arg.find(",", pos2 + 1);
        this->coordRobot.x = std::stof(arg.substr(0, pos1));
        this->coordRobot.y = std::stof(arg.substr(pos1 + 1, pos2 - pos1 - 1));
        this->coordRobot.a = std::stof(arg.substr(pos2 + 1, pos3 - pos2 - 1));
    }
    if(lp.isPoint)
    {
        Coord pointCoord = this->localizePoint(lp);
        SendedPoint sp;
        sp.x = pointCoord.x;
        sp.y = pointCoord.y;
        sp.a = pointCoord.a;
        sp.quality = lp.quality;
        sp.isObstacle = lp.obstacle;
        CommunicationData data;
        data.persistence = COMM_PERSISTENCE::ERASE_NEXT_LOOP;
        data.action = CommAction::LIDAR_DETECTION;
        data.argument = std::to_string(sp.x) + "," + std::to_string(sp.y) + "," + std::to_string(sp.a) + "," + std::to_string(sp.quality) + "," + std::to_string(sp.isObstacle);
        this->communication.envoyer(data);
    }
}
CarteLidar::LidarPoint CarteLidar::detect()
{
    LidarPoint lp;
    if(IS_OK(lidar.waitPoint()))
    {
        RPLidarMeasurement m = lidar.getCurrentPoint();
        lp.isPoint = true;
        lp.angle = m.angle;
        lp.distance = m.distance / 1000.0; // convert mm to m
        lp.quality = m.quality;
        if(m.distance < 0.5) lp.obstacle = true;
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
