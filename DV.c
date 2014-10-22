#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  Shift,          sensorDigitalOut)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           LIntake,       tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           FRBase,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           BRBase,        tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port4,           BLBase,        tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port5,           FLBase,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           RTrans,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           LTrans,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LLift,         tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port9,           RLift,         tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          RIntake,       tmotorVex393_HBridge, openLoop)

#pragma platform(VEX)

//Competition Cont rol and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void clear(){
	nMotorEncoder[BLBase] = 0;
	nMotorEncoder[BRBase] = 0;
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
	motor[RLift] = 0;
	motor[LLift] = 0;
	motor[LTrans] = 0;
 	motor[RTrans] = 0;
 	motor[LIntake] = 0;
	motor[RIntake] = 0;
}

void right(int speed){
	motor[FRBase] = speed;
	motor[BRBase] = speed;
}

void left(int speed){
	motor[FLBase] = speed;
	motor[BLBase] = speed;
}

void forward(int distance, int speed){
	while(nMotorEncoder[BLBase] < distance && nMotorEncoder[BRBase] > -distance){
		right(speed);
		left(speed);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

void backward(int distance, int speed){
	while(nMotorEncoder[BLBase] > -distance && nMotorEncoder[BRBase] < distance){
			right(-speed);
			left(-speed);
		}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

//For turns, adjust speed argument individually to allow distance travel
void turnRight(int distance, int speed){
	while(nMotorEncoder[BLBase] < distance && nMotorEncoder[BRBase] < distance){
		right(-speed);
		left(speed);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

void turnLeft(int distance, int speed){
	while(nMotorEncoder[BLBase] > -distance && nMotorEncoder[BRBase] > -distance){
		left(-speed);
		right(speed);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

void swingRight(int distance, int speed){
	while(nMotorEncoder[BLBase] < distance){
		right(speed/2);
		left(speed);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}


void swingLeft(int distance, int speed, ){
	while(nMotorEncoder[BRBase] > -distance){
		left(speed/2);
		right(speed);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

//Ray and Navu suggest only measuring angles for necessary heights
void lift(int height, int speed){
	while(height > nMotorEncoder[LLift])
	{
		motor[RLift] = speed;
		motor[LLift] = speed;
		motor[LTrans] = speed;
	 	motor[RTrans] = speed;
	}
	motor[RLift] = 0;
	motor[LLift] = 0;
	motor[LTrans] = 0;
 	motor[RTrans] = 0;
}

void down(int time, int speed){
	motor[RLift] = -speed;
	motor[LLift] = -speed;
	motor[LTrans] = -speed;
	motor[RTrans] = -speed;
	wait10Msec(time);
	motor[RLift] = 0;
	motor[LLift] = 0;
	motor[LTrans] = 0;
 	motor[RTrans] = 0;
}

void intake(int time, int speed){
	motor[LIntake] = speed;
	motor[RIntake] = speed;
	wait10Msec(time);
	motor[LIntake] = 0;
	motor[RIntake] = 0;
}

void transmission(){
	if(SensorValue[Shift] == 0)
		SensorValue[Shift] = 1;
	else if(SensorValue[Shift] == 1)
		SensorValue[Shift] = 0;
}

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	clear();
	nMotorEncoder[LLift] = 0;
	lift(200, 127);
	intake(90, -127);
	down(10, 60);
	forward(220, 50);
  clear();
  intake(160, 127);
  lift(1360, 127);
  Sleep(50);
    turnRight(50 ,100);
  forward(600, 50);
  clear();
  intake(300, -127);
	/*
  forward(220, 100);
  clear();
  intake(120, 127);
  clear();
  //turnRight(720, 127);
  backward(220, 127);
  Sleep(50);
  clear();
  turnRight(320, 127);
  Sleep(50);
  clear();
  forward(320, 127);
  clear();
  /*
  clear();
  intake();
  turnRight();
  clear();
  lift();
  forward();
  clear();
  intake(-127);
  backward(x, 127);
  */

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	SensorValue[Shift] = 0;
	while(true)
	{
		if(SensorValue[Shift] == 1)
		{
			motor[LTrans] = vexRT[Ch3];
			motor[FLBase] = vexRT[Ch3];
			motor[BLBase] = vexRT[Ch3];
	 		motor[RTrans] = vexRT[Ch2];
	 		motor[FRBase] = vexRT[Ch2];
	 		motor[BRBase] = vexRT[Ch2];
	 		if(vexRT[Btn5U] == 1)
	 		{
	 			motor[LLift] = 127;
	 			motor[RLift] = 127;
	 		}
	 		else if(vexRT[Btn5D] == 1)
	 		{
	 			motor[LLift] = -127;
	 			motor[RLift] = -127;
	 		}
	 		else
	 		{
	 			motor[LLift] = 0;
	 			motor[RLift] = 0;
	 		}
	 		if(vexRT[Btn8U] == 1)
	 		{
	 			SensorValue[Shift] = 0;
	 			wait10Msec(50);
	 		}
	 		/*
	 		if(vexRT[Btn8D] == 1)
	 		{
	 			trans = false;
	 			SensorValue[Shift] = 1;
	 			for(int x=0; x<5; x++)
	 			{
	 				motor[LTrans] = 50;
	 				motor[RTrans] = 50;
	 				motor[LLift] = 50;
	 				motor[RLift] = 50;
					motor[FLBase] = 50;
					motor[BLBase] = 50;
			 		motor[FRBase] = 50;
	 				motor[BRBase] = 50;
	 				wait10Msec(5);
	 				motor[LTrans] = -50;
	 				motor[RTrans] = -50;
	 				motor[LLift] = -50;
	 				motor[RLift] = -50;
					motor[FLBase] = -50;
					motor[BLBase] = -50;
			 		motor[FRBase] = -50;
	 				motor[BRBase] = -50;
	 				wait10Msec(5);
	 			}
	 			*/

		}
		if(SensorValue[Shift] == 0)
		{
			motor[FLBase] = vexRT[Ch3];
			motor[BLBase] = vexRT[Ch3];
	 		motor[FRBase] = vexRT[Ch2];
	 		motor[BRBase] = vexRT[Ch2];
	 		if(vexRT[Btn5U] == 1)
	 		{
	 			if(vexRT[Btn7U] == 0)
	 				if(nMotorEncoder[LLift] < 1000)
	 				{
	 					motor[LLift] = 127;
	 					motor[RLift] = 127;
	 					motor[LTrans] = 127;
	 					motor[RTrans] = 127;
	 				}
	 				else if(nMotorEncoder[LLift] > 1000)
	 				{
	 					motor[LLift] = 100;
	 					motor[RLift] = 100;
	 					motor[LTrans] = 100;
	 					motor[RTrans] = 100;
	 				}
	 			if(vexRT[Btn7U] == 1)
	 				if(nMotorEncoder[LLift] < 1000)
	 				{
	 					motor[LLift] = 127/2;
	 					motor[RLift] = 127/2;
	 					motor[LTrans] = 127/2;
	 					motor[RTrans] = 127/2;
	 				}
	 				else if(nMotorEncoder[LLift] > 1000)
	 				{
	 					motor[LLift] = 50;
	 					motor[RLift] = 50;
	 					motor[LTrans] = 50;
	 					motor[RTrans] = 50;
	 				}

	 		}
	 		else if(vexRT[Btn5D] == 1)
	 		{
	 			motor[LLift] = -127;
	 			motor[RLift] = -127;
	 			motor[LTrans] = -127;
	 			motor[RTrans] = -127;
	 		}
	 		else
	 		{
	 			motor[LLift] = 0;
	 			motor[RLift] = 0;
	 			motor[LTrans] = 0;
	 			motor[RTrans] = 0;
	 		}
	 		if(vexRT[Btn8U] == 1)
	 		{
	 			SensorValue[Shift] = 1;
	 			wait10Msec(50);
	 		}
	 		/*
	 		if(vexRT[Btn8U] == 1)
	 		{
	 			trans = true;
	 			motor[LTrans] = 127;
	 			motor[RTrans] = 127;
	 			SensorValue[Shift] = 0;
	 			wait10Msec(50);
	 		}
	 		if(vexRT[Btn8D] == 1)
	 		{
	 			trans = true;
	 			motor[LTrans] = 127;
	 			motor[RTrans] = 127;
	 			SensorValue[Shift] = 0;
	 			for(int x=0; x<5; x++)
	 			{
	 				motor[LTrans] = -50;
	 				motor[RTrans] = -50;
	 				motor[LLift] = 50;
	 				motor[RLift] = 50;
					motor[FLBase] = 50;
					motor[BLBase] = 50;
			 		motor[FRBase] = 50;
	 				motor[BRBase] = 50;
	 				wait10Msec(5);
	 				motor[LTrans] = 50;
	 				motor[RTrans] = 50;
	 				motor[LLift] = -50;
	 				motor[RLift] = -50;
					motor[FLBase] = -50;
					motor[BLBase] = -50;
			 		motor[FRBase] = -50;
	 				motor[BRBase] = -50;
	 				wait10Msec(5);
	 			}
	 			*/

		}
		if(vexRT[Btn6U] == 1)
		{
			motor[LIntake] = 127;
			motor[RIntake] = 127;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[LIntake] = -127;
			motor[RIntake] = -127;
		}
		else
		{
			motor[LIntake] = 0;
			motor[RIntake] = 0;
		}
		if(vexRT[Btn7L] == 1)
		{
			startTask(autonomous);
			stopTask(usercontrol);
		}

	}
}
