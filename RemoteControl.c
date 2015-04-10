#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     ,               sensorLightActive)
#pragma config(Sensor, S3,     ,               sensorLightActive)
#pragma config(Sensor, S4,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     liftb,         tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     liftt,         tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     rightt,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rightb,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     leftt,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     leftb,         tmotorTetrix, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
	// Place code here to sinitialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
	motor[liftb] = motor[liftt] = 0;

	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase
	nMotorEncoder[liftb] = 0;
	nMotorEncoder[liftt] = 0;
	const int threshold = 25;
	const int lowerpeg = 73;
	const int middlepeg = 445;
	const int upperpeg = 855;

	while (true)
	{
		nxtDisplayTextLine(2, "Human_Control");
		//wait1Msec(5);

		getJoystickSettings(joystick);





		if (joystick.joy1_y1 > threshold) //if its greater than 15, move at a joystick value - 15
			motor [leftb] = motor[leftt] = joystick.joy1_y1 - threshold;

		else if (joystick.joy1_y1 <= threshold && joystick.joy1_y1 >= -threshold)//if its between negative 15 and 15, it doesn't move
			motor[leftb] = motor[leftt] = 0;


		else if (joystick.joy1_y1 < -threshold)
			motor [leftb] = motor [leftt] =joystick.joy1_y1 +threshold;
		getJoystickSettings(joystick);


		if (joystick.joy1_y2 > threshold) //if its greater than 15, move at a joystick value - 15
			motor [rightb] =motor[rightt] = joystick.joy1_y2 - threshold;

		else if (joystick.joy1_y2 <= threshold && joystick.joy1_y2 >= -threshold)//if its between negative 15 and 15, it doesn't move
			motor[rightb] = motor[rightt] = 0;



		else if (joystick.joy1_y2 < -threshold) // if its less than 15 move at joystick value + 15
			motor [rightb] =motor[rightt] = joystick.joy1_y2 + threshold;

		if (joy1Btn(4) == 1)
		{
			motor[liftb] = motor[liftt] = 20;
		}


		if (joy1Btn(2) == 1)
		{
			motor[liftb] = motor[liftt] = -13;
		}

		if (joy1Btn(4) == 0 && joy1Btn(2) == 0 && joy2Btn(1) == 0 && joy2Btn(2) == 0 && joy2Btn(3) == 0 && joy2Btn(4) == 0 && abs(joystick.joy2_y2) < threshold )
		{
			motor[liftb] = 0;
			motor[liftt] = 0;
		}

		getJoystickSettings(joystick);

		if (joy2Btn(1) == 1 && joy1Btn(2) == 0 && joy1Btn(4) ==0 && abs(joystick.joy2_y2) < threshold )
		{
			if (nMotorEncoder[liftt] < lowerpeg)
				motor[liftb] = motor[liftt] = 15;
			else if (nMotorEncoder[liftt] > lowerpeg)
				motor[liftb] = motor[liftt] = 0;

		}
		else if (joy2Btn(2) == 1 && joy1Btn(2) == 0 && joy1Btn(4) ==0 && abs(joystick.joy2_y2) < threshold )
		{
			if (nMotorEncoder[liftt] < middlepeg)
				motor[liftb] = motor[liftt] = 15;
			else if (nMotorEncoder[liftt] > middlepeg)
				motor[liftb] = motor[liftt] = 0;
		}

		else if (joy2Btn(3) == 1 && joy1Btn(2) == 0 && joy1Btn(4) ==0 && abs(joystick.joy2_y2) < threshold )
		{
			if (nMotorEncoder[liftt] < upperpeg)
				motor[liftb] = motor[liftt] = 15;
			else if (nMotorEncoder[liftt] > upperpeg)
				motor[liftb] = motor[liftt] = 0;
		}

		else if (joy2Btn(4) == 1 && joy1Btn(2) == 0 && joy1Btn(4) ==0 && abs(joystick.joy2_y2) < threshold )
		{
			if (nMotorEncoder[liftt] > 0)
				motor[liftb] = motor[liftt] = -20;
			else
				motor[liftb] = motor[liftt] = 0;
		}

		if (joy1Btn(2) == 0 && joy1Btn(4) == 0 && abs(joystick.joy2_y2) > threshold)
		{
			if (joystick.joy2_y2 >0 )
				motor[liftt] = motor[liftb] = 9;
			else
				motor[liftt] = motor[liftb] = -9;
		}



	}
}
