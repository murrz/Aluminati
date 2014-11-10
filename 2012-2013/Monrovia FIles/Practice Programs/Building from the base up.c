#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,      ,              sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     RightBase,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     Arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     LeftBase,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_2,     Elev,          tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

#define MOTOR_THRESHOLD 50
#define MOTORVAL(X) ((X>MOTOR_THRESHOLD)? 100: ((X<-MOTOR_THRESHOLD)? -100: 0))

void main_wheel(int xVal, int yVal){
	motor[RightBase] = (MOTORVAL(xVal + yVal));
	motor[LeftBase] = (MOTORVAL(yVal - xVal));
}



task main()
{
	while(true){
		getJoystickSettings(joystick);
		main_wheel(joystick.joy1_x1, joystick.joy1_y1);
	}
}