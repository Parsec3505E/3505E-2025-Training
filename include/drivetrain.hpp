#include "api.h"
class Drivetrain{
    std::unique_ptr<pros::MotorGroup> leftSide;
    std::unique_ptr<pros::MotorGroup> rightSide;

    public:
        Drivetrain(std::vector<std::int8_t> leftMotorPorts, std::vector<std::int8_t> rightMotorPorts);
        void updateDrivetrain(pros::Controller &master);
};