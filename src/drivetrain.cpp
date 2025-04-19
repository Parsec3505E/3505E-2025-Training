#include "drivetrain.hpp"

DriveTrain::DriveTrain(std::vector<std::int8_t> leftMotorPorts, std::vector<std::int8_t> rightMotorPorts, int gyroPort){
    // Left motor pair
    leftSide = std::unique_ptr<pros::MotorGroup>{new pros::MotorGroup{leftMotorPorts}};
    leftSide->set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    leftSide->set_gearing_all(pros::E_MOTOR_GEAR_BLUE);

    // Right motor pair
    rightSide = std::unique_ptr<pros::MotorGroup>{new pros::MotorGroup{rightMotorPorts}};
    rightSide->set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    rightSide->set_gearing_all(pros::E_MOTOR_GEAR_BLUE);

    // Gyro 
    gyro = std::unique_ptr<pros::Imu>{new pros::Imu{gyroPort}};
}

// Code for the updateDriveTrain function
void DriveTrain::updateDriveTrain(pros::Controller &master){
    // Creates variables for the left and right joystick
    float scaleFactor = 600/127;
    float leftJoyStick = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)*scaleFactor;
    float rightJoyStick = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)*scaleFactor;

    if (abs(leftJoyStick) <= 5){
        leftJoyStick = 0;
    }

    if (abs(rightJoyStick) <= 5){
        rightJoyStick = 0;
    }

    leftSide->move_velocity(leftJoyStick + rightJoyStick);
    rightSide->move_velocity(leftJoyStick - rightJoyStick);
}

void DriveTrain::moveStraight(float speed, float heading, float distance, float kP){
    // Set position to zero 
    leftSide->tare_position_all();
    rightSide->tare_position_all();

    // While the distance is not met
    while(abs((leftSide->get_position() + rightSide->get_position())/2) < distance){
        // Creates the errors
        float error = heading-gyro->get_heading();

        // Sets turn and makes sure that it would turn properly
        if (error > 180){
            error = error - 360;
        }  
        
        else if (error < -180) {
            error = 360 + error;
        }

        // Moves the motor
        leftSide->move_velocity(speed + kP*(error));
        rightSide->move_velocity(speed - kP*(error));
        pros::delay(20);

    }

    // Stops the motors
    leftSide->move_velocity(0);
    rightSide->move_velocity(0);
}