#include "drivetrain.hpp"
Drivetrain::Drivetrain(std::vector<std::int8_t> leftMotorPorts, std::vector<std::int8_t> rightMotorPorts){
    leftSide = std::unique_ptr<pros::MotorGroup>(new pros::MotorGroup(leftMotorPorts));
    rightSide = std::unique_ptr<pros::MotorGroup>(new pros::MotorGroup(rightMotorPorts));
    leftSide->set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    rightSide->set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    leftSide->set_gearing(pros::E_MOTOR_GEAR_BLUE);
    rightSide->set_gearing(pros::E_MOTOR_GEAR_BLUE);
}

void Drivetrain::updateDrivetrain(pros::Controller &master){
    float speedL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)*(600/127);

    if (abs(speedL) <= 5){
        speedL = 0;
    }


    float speedR = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)*(600/127);
    if (abs(speedR) <= 5){
        speedR = 0;
    }

    
    
    leftSide->move_velocity(speedL+speedR);
    rightSide->move_velocity(speedL-speedR);




}