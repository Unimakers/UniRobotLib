#pragma once
#include <RPLidar.h>
#include <Common/coord.hpp>
#include <Common/robotConfig.hpp>
// #include <Common/communication.hpp>
#include <Common/communication_simplified.hpp>
class CarteLidar {
    /// @brief the lidar point res structure
    struct LidarPoint{
        /// @brief is there a valid point
        bool isPoint=false;
        /// @brief the distance in meters
        float distance=0;
        /// @brief the angle
        float angle=0;
        /// @brief the quality of detection
        float quality=0;
        /// @brief is the point considered an obstacle
        bool obstacle=false;
    };
    struct SendedPoint{
        /// @brief x coord
        float x;
        /// @brief y coord
        float y;
        /// @brief angle
        float a;
        /// @brief quality
        float quality;
        /// @brief isObstacle
        bool isObstacle;
    };
    Coord coordRobot;
    CommEsclave communication;
    RobotConfig robotConfig;
    RPLidar lidar;
    bool hasObstacle = false;
    public:
    /// @brief class object init
    CarteLidar();
    /// @brief the lidar setup code
    void setup(RobotConfig config);
    /// @brief the lidar main loop
    void loop();
    /// @brief the lidar detect function
    /// @return the lidarPoint
    LidarPoint detect();
    /// @brief function to localize a point relatively to the robot coords
    /// @param lp the lidarPoint
    /// @return the coords of the lidarPoint
    Coord localizePoint(LidarPoint lp);
};
