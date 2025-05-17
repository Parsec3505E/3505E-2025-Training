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

    if (fabs(leftJoyStick) <= 5){
        leftJoyStick = 0;
    }

    if (fabs(rightJoyStick) <= 5){
        rightJoyStick = 0;
    }

    leftSide->move_velocity(leftJoyStick + rightJoyStick);
    rightSide->move_velocity(leftJoyStick - rightJoyStick);
}

void DriveTrain::moveStraight(float speed, float heading, float distance, float kP, float accRate, float decRate, float minSpeed, float wheelSize){
    // Start time when the function began running
    unsigned long long startTime = pros::millis();

    // Set position to zero 
    leftSide->tare_position_all();
    rightSide->tare_position_all();

    // Converts distance in ticks to distance in rotations (300 ticks = 1 rotation)
    float circumference = 2 * M_PI * (wheelSize/2);
    distance = (distance / circumference) * 300;

    // While the distance is not met
    while(fabs((leftSide->get_position() + rightSide->get_position())/2) < distance){
        // Creates the errors
        float error = heading-gyro->get_heading();
        float distanceError = distance - ((leftSide->get_position() + rightSide->get_position())/2);

        // Creates elapsed time variable to use for acceleration
        unsigned long long elapsedTime = pros::millis() - startTime;

        // Acceleration & deceleration values
        float accLine = accRate * elapsedTime + minSpeed;
        float maxSpeed = speed;
        float decLine = decRate * distanceError + minSpeed;

        // Gets the maximum or minumum speed for movement and involves acceleration and deceleration
        if (speed < 0){
            maxSpeed = std::max({accLine, maxSpeed, decLine});
        } else {
            maxSpeed = std::min({accLine, maxSpeed, decLine});
        }

        // Sets turn and makes sure that it would turn properly
        if (error > 180){
            error = error - 360;
        }  
        else if (error < -180) {
            error = 360 + error;
        }

        // Moves the motor based on the steer (the drift)
        leftSide->move_velocity(maxSpeed + kP*(error));
        rightSide->move_velocity(maxSpeed - kP*(error));
        pros::delay(20);

    }

    // Stops the motors
    leftSide->move_velocity(0);
    rightSide->move_velocity(0);
}