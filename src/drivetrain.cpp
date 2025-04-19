#include "drivetrain.hpp"

Drivetrain::Drivetrain(std::vector<std::int8_t>leftMotorPorts, std::vector<std::int8_t>rightMotorPorts, int gyroPort){

    leftSide = std::unique_ptr<pros::MotorGroup>{new pros::MotorGroup{leftMotorPorts}};
    rightSide = std::unique_ptr<pros::MotorGroup>{new pros::MotorGroup{rightMotorPorts}};
    gyro = std::unique_ptr<pros::Imu>{new pros::Imu{gyroPort}};
    leftSide->set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    leftSide->set_gearing_all(pros::E_MOTOR_GEAR_BLUE);
    rightSide->set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    rightSide->set_gearing_all(pros::E_MOTOR_GEAR_BLUE);

}

void Drivetrain::updateDrivetrain(pros::Controller &master){

    float leftJoystick = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * 600/127;
    float rightJoystick = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 600/127;

    if (abs(leftJoystick) < 5){
        leftJoystick = 0;
    }
    if (abs(rightJoystick) < 5){
        rightJoystick = 0;
    }

    leftSide-> move_velocity(leftJoystick + rightJoystick);
    rightSide-> move_velocity(leftJoystick - rightJoystick);

}

void Drivetrain::moveStraight(float speed, float heading, float distance, float kP){
    leftSide->tare_position_all();
    rightSide->tare_position_all();

    while(abs((rightSide->get_position())+ abs(leftSide->get_position()))/2 < distance){
        float curAngle = gyro->get_heading();
        float error = heading - curAngle;
        if (error > 180){
            error = error-360;
        } else if(error < -180){
            error = 360 + error;
        } 
        leftSide->move_velocity(speed + error*kP);
        rightSide->move_velocity(speed - error*kP);
        pros::delay(20);
    }
    leftSide->move_velocity(0);
    rightSide->move_velocity(0);
}