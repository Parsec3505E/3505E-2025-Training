#include "drivetrain.hpp"

DriveTrain::DriveTrain(std::vector<std::int8_t> leftMotorPorts, std::vector<std::int8_t> rightMotorPorts, int gyroPort){
    leftSide = std::unique_ptr<pros::MotorGroup>{new pros::MotorGroup{leftMotorPorts}};
    leftSide->set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    leftSide->set_gearing_all(pros::E_MOTOR_GEAR_BLUE);

    rightSide = std::unique_ptr<pros::MotorGroup>{new pros::MotorGroup{rightMotorPorts}};
    rightSide->set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    rightSide->set_gearing_all(pros::E_MOTOR_GEAR_BLUE);
}

// Code for the updateDriveTrain function
void DriveTrain::updateDriveTrain(pros::Controller &master){
    leftSide->move_velocity(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    rightSide->move_velocity(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
}