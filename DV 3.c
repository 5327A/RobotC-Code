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

void clear(){									//Clears all values and resets them to 0(Motors and Encoders)
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

void right(int speed){				//Power right side base motors
	motor[FRBase] = speed;
	motor[BRBase] = speed;
}

void left(int speed){					//Power left side base motors
	motor[FLBase] = speed;
	motor[BLBase] = speed;
}

void forward(int distance, int speed){		//Move Forward
	while(nMotorEncoder[BLBase] < distance && nMotorEncoder[BRBase] > -distance){
		right(speed);
		left(speed);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

void backward(int distance, int speed){		//Move Backwards
	while(nMotorEncoder[BLBase] > -distance && nMotorEncoder[BRBase] < distance){
			right(-speed);
			left(-speed);
		}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

void turnRight(int distance, int speed){	//Turn Right
	while(nMotorEncoder[BLBase] < distance && nMotorEncoder[BRBase] < distance){
		right(-speed);
		left(speed);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

void turnLeft(int distance, int speed){		//Turn Left
	while(nMotorEncoder[BLBase] > -distance && nMotorEncoder[BRBase] > -distance){
		left(-speed);
		right(speed);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

void swingRight(int distance, int speed){	//Swing(One motor moves 1/2 speed of other) Right
	while(nMotorEncoder[BLBase] < distance){
		right(speed/2);
		left(speed);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}


void swingLeft(int distance, int speed, ){//Swing(One motor moves 1/2 speed of other) Left
	while(nMotorEncoder[BRBase] > -distance){
		left(speed/2);
		right(speed);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

void lift(int height, int speed){					//Lift to a specific height
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

void down(int time, int speed){						//Retract lift downwards
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

void intake(int time, int speed){					//Intake/Outtake
	motor[LIntake] = speed;
	motor[RIntake] = speed;
	wait10Msec(time);
	motor[LIntake] = 0;
	motor[RIntake] = 0;
}

void transmission(){											//Change transmission mode
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

	//Setup Phase
	clear();
	nMotorEncoder[LLift] = 0;
	lift(150, 127);
  backward(400, 127);
  lift(150, 127);
  //Outtake Cubes
  intake(200, -127);
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
	SensorValue[Shift] = 0;						//Pnuematic Default Position
	while(true)
	{
		if(SensorValue[Shift] == 1)			//6 Motor Drive Mode
		{
			motor[LTrans] = vexRT[Ch3];
			motor[FLBase] = vexRT[Ch3];
			motor[BLBase] = vexRT[Ch3];
	 		motor[RTrans] = vexRT[Ch2];
	 		motor[FRBase] = vexRT[Ch2];
	 		motor[BRBase] = vexRT[Ch2];
	 		if(vexRT[Btn5U] == 1)					//Lift Up
	 		{
	 			motor[LLift] = 127;
	 			motor[RLift] = 127;
	 		}
	 		else if(vexRT[Btn5D] == 1)		//Retract Lift Down
	 		{
	 			motor[LLift] = -127;
	 			motor[RLift] = -127;
	 		}
	 		else
	 		{
	 			motor[LLift] = 0;
	 			motor[RLift] = 0;
	 		}
	 		if(vexRT[Btn8U] == 1)					//Shift to 4 Motor Base
	 		{
	 			SensorValue[Shift] = 0;
	 			wait10Msec(50);
	 		}

		}																//4 Motor Base Mode
		if(SensorValue[Shift] == 0)
		{
			motor[FLBase] = vexRT[Ch3];
			motor[BLBase] = vexRT[Ch3];
	 		motor[FRBase] = vexRT[Ch2];
	 		motor[BRBase] = vexRT[Ch2];
	 		if(vexRT[Btn5U] == 1)					//Lift Up, Speed Dependant on Height
	 		{
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
	 		}
	 		else if(vexRT[Btn5D] == 1)			//Retract Lift Downwards
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
	 		if(vexRT[Btn8U] == 1)						//Shift to 6 Motor Drive
	 		{
	 			SensorValue[Shift] = 1;
	 			wait10Msec(50);
	 		}
		}
		if(vexRT[Btn6U] == 1)							//Intake
		{
			motor[LIntake] = 127;
			motor[RIntake] = 127;
		}
		else if(vexRT[Btn6D] == 1)				//Outtake
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
