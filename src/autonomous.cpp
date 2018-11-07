#include <math.h>
#include <C:\Users\RD SINGH\Desktop\General\Robotics\PROS\include\main.h>
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

 void move(double targetDistance, int maxPower)
{
	double kp = 0.1;
	double kd = 0.1;
  double MIN_POWER = 1;
	/* Variables used to calculate how fast bot is moving*/
	double wheelDiameter = 4;
	double circumference = wheelDiameter * M_PI; //Roughly 14.13 inches
	double currentDistance = 0;
	double error = 1, lastError = 0, integral = 0;
	double derivative = 0;
	int power = 0, powerLeft = 0, powerRight = 0;

  pros::Motor lfdMotor (1, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor rfdMotor (1, pros::E_MOTOR_ENCODER_DEGREES);


	while(error != 0)
	{
		currentDistance = (lfdMotor.get_position() + rfdMotor.get_position())/2;

		error = targetDistance - currentDistance;


		derivative = error - lastError;
		lastError = error;

		power = (error * kp) + (derivative * kd);

		if(power > 0)
		{
			if(power > maxPower)
			{
				power = maxPower;
			}
			else if(power < MIN_POWER)
			{
				power = MIN_POWER;
			}
		}
		else if(power < 0)
		{
			if(power < -maxPower)
			{
				power = -maxPower;
			}
			else if(power > -MIN_POWER)
			{
				power = -MIN_POWER;
			}
		}
		powerLeft = power;
		powerRight = power;
/*
		motor[frontL] = powerLeft;
		motor[backL] = powerLeft;
		motor[frontR] = powerRight;
		motor[backR] = powerRight;
*/
	}

}

void autonomous()
{

}
