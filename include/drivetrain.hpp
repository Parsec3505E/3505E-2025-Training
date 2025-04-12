#include api.h
class Drivetrain{
    pros::MotorGroup* leftSide;
    pros::MotorGroup* rightSide;
    std::unique-ptc<pros::MotorGroup> leftSide;
    public:
        Drivetrain(std::vector<std::int8_t> leftMotorPorts, std::vector<std::int8_t> rightMotorPorts);
        void updateDrivetrain(pros::Controller &master);
};