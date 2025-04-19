#include "api.h"

// Creates drivetrain class
class DriveTrain {

    // Creates pointers for the motorgroup
    std::unique_ptr<pros::MotorGroup> leftSide;
    std::unique_ptr<pros::MotorGroup> rightSide;
    std::unique_ptr<pros::Imu> gyro;


    public: 
        DriveTrain(std::vector<std::int8_t> leftMotorPorts, std::vector<std::int8_t> rightMotorPorts, int gyroPort);

        // Creates the updateDriveTrain function
        void updateDriveTrain(pros::Controller &master);
        void moveStraight(float speed, float heading, float distance, float kP);
};