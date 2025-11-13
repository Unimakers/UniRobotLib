#include <RPLidar.h>
#include <coord.hpp>
class CarteLidar {
    /// @brief the lidar point res structure
    struct LidarPoint{
        /// @brief the distance in meters
        float distance=0;
        /// @brief the angle
        float angle=0;
        /// @brief the quality of detection
        float quality=0;
    };
    public:
    /// @brief class object init
    CarteLidar();
    /// @brief the lidar setup code
    void setup();
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
