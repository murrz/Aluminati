#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          leftclaw,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightclaw,     tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorRightRear, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorRightFront, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorLeftFront, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorLeftRear, tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#define TIME_INTERVAL  5


#define LOAD(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!//
#define DEADBAND(x) ((abs(x) >= 10)? x: 0)

#define SERVO_AMOUNT 90

void left_base(int joy_x)
{
	 float k=.3;
	 int drivePower;

   joy_x = k*joy_x;
   drivePower = DEADBAND(joy_x);

   motor[motorLeftFront] = LOAD(drivePower);
   motor[motorLeftRear] = LOAD(drivePower);
}

void right_base (int joy_y)
{
	 float k=.3;
	 int drivePower;

   joy_y = k*joy_y;
   drivePower = DEADBAND(joy_y);

   motor[motorRightFront] = LOAD(drivePower);
   motor[motorRightRear] = LOAD(drivePower);
}

void move(int joy_x, int joy_y) {
	float	k=.3;
	int		leftDrivePower, rightDrivePower;
	float	rightPlusLeft, rightMinusLeft;

	joy_x = -DEADBAND(joy_x);
	joy_y =  DEADBAND(joy_y);

	rightPlusLeft		= (127-abs(joy_x))*(joy_y/127) + joy_y;
	rightMinusLeft	= (127-abs(joy_y))*(joy_x/127) + joy_x;

	leftDrivePower	= (((rightPlusLeft - rightMinusLeft)/2)/127)*100;
	rightDrivePower = (((rightPlusLeft + rightMinusLeft)/2)/127)*100;

	motor[motorRightFront]	= k*rightDrivePower;
	motor[motorRightRear]		= k*rightDrivePower;
	motor[motorLeftFront]		= k*leftDrivePower;
	motor[motorLeftRear]		= k*leftDrivePower;
}

void open_claw (int btn_x)
{
	if (btn_x == 1)
	{
		motor[motorA] = 30;
		motor[motorB] = -30;
	}
}

void close_claw (int btn_x)
{
	if (btn_x == 1)
	{
		motor[motorA] = -30;
		motor[motorB] = 30;
	}
}

/*void clear_claw_encoder (int btn_x)
{
	  nMotorEncoder[motorC] = 0;  //clear the LEGO encoders in motors B and C+
  	nMotorEncoder[motorB] = 0;
}

void open_claw (int btn_x)
{
	if (btn_x == 1)
	{
		nMotorEncoder[motorB] = 0;                // reset the Motor Encoder of Motor B
		nMotorEncoderTarget[motorB] = SERVO_AMOUNT;        // set the  target for Motor Encoder of Motor B to 30
		nMotorEncoderTarget[motorA] = SERVO_AMOUNT;
		motor[motorB] = 30;                       // motor B is run at a power level of 75
		motor[motorA] = -30;                       // motor C is run at a power level of 75

		while(nMotorRunState[motorB] != runStateIdle)  // while Motor B is still running:
			{
	  		// do not continue
			}
		motor[motorB] = 0;                       // motor B is stopped at a power level of 0
		motor[motorC] = 0;                       // motor C is stopped at a power level of 0
	}
}

void close_claw (int btn_x)
{
	if (btn_x == 1)
	{
		nMotorEncoder[motorB] = 0;                // reset the Motor Encoder of Motor B
		nMotorEncoderTarget[motorB] = SERVO_AMOUNT;        // set the  target for Motor Encoder of Motor B to 30
		nMotorEncoderTarget[motorA] = SERVO_AMOUNT;
		motor[motorB] = -30;                       // motor B is run at a power level of 75
		motor[motorA] = 30;                       // motor C is run at a power level of 75

		while(nMotorRunState[motorB] != runStateIdle)  // while Motor B is still running:
			{
	  		// do not continue
			}
		motor[motorB] = 0;                       // motor B is stopped at a power level of 0
		motor[motorC] = 0;                       // motor C is stopped at a power level of 0
	}
}
*/

/*void open_claw (int btn_x)
{
	float k;
	k = 30;

	while (nMotorEncoder[leftclaw] < 20) //while the encoder wheel turns 20 bits
  	{
    	motor[leftclaw] = k; //turn both motors on at 30 percent power
    	motor[rightclaw] = k;
  	}

  	motor[leftclaw] = 0; //turn both motors off
  	motor[rightclaw] = 0;
}
void close_claw (int btn_x)
{
		float k;
		k = -30;

	while (nMotorEncoder[leftclaw] < 20) //while the encoder wheel turns 20 bits
  	{
    	motor[leftclaw] = k; //turn both motors on at 30 percent power
    	motor[rightclaw] = k;
  	}

  	motor[leftclaw] = 0; //turn both motors off
  	motor[rightclaw] = 0;
}
*/

/*void open_claw (int btn_x)
{
		float k;

		k = 50;
		motor[leftclaw] = k;
		motor[rightclaw] = k;
}

void close_claw (int btn_x)
{
		float k;

		k = -50;
		motor[leftclaw] = k;
		motor[rightclaw] = k;
}
*/

bool tank = false;

task main()
{
	//initializeRobot();
	while(true)
	{
		getJoystickSettings(joystick);
		if (joy1Btn(10) == 1)
			if (tank == false)
				tank = true;
			else
				tank = false;
		if (tank == true)
		{
			left_base(joystick.joy1_y1);
			right_base(joystick.joy1_y2);
		}

		if (tank == false)
			move(joystick.joy1_x1, joystick.joy1_y1);
		open_claw(joy1Btn(4));
		close_claw(joy1Btn(2));
		if (joy1Btn(4) != 1 && joy1Btn(2) != 1)
		{
			motor[motorA] = 0;
			motor[motorB] = 0;
		}

		wait1Msec(TIME_INTERVAL);
	}

}
