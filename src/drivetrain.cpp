#include "drivetrain.hpp"
Drivetrain::Drivetrain(std::vector<std::int8_t> leftMotorPorts, std::vector<std::int8_t> rightMotorPorts){
    leftSide = std::unique_ptr<pros::MotorGroup>(new pres::MotorGroup(leftMotorPorts));
    rightSide = std::unique_ptr<pros::MotorGroup>(new pres::MotorGroup(rightMotorPorts));
    leftSide->set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    rightSide->set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    leftSide->set_brake_mode_all(pros::E_MOTOR_GEAR_BLUE);
    rightSide->set_brake_mode_all(pros::E_MOTOR_GEAR_BLUE);
}

void Drivetrain::updateDrivetrain(pros::Controller &master){
    float speedL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)
    
    leftSide->move_velocity(50);
    rightSide->move_velocity(50);
}