#include "api.h"

class Drivetrain{
    std::unique_ptr<pros::MotorGroup>leftSide;
    std::unique_ptr<pros::MotorGroup>rightSide;
    std::unique_ptr<pros::Imu>gyro;
    public: 
        Drivetrain(std::vector<std::int8_t>leftMotorPorts, std::vector<std::int8_t>rightMotorPorts, int gyroPort);

        void updateDrivetrain(pros::Controller &master);
        void moveStraight(float speed, float heading, float distance, float kP);

};