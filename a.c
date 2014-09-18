#pragma config(Sensor, dgtl1,  Shift,          sensorDigitalOut)
#pragma config(Motor,  port1,           LIntake,       tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           FRBase,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           FLBase,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           BRBase,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           BLBase,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           LTrans,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           RTrans,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LLift,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           RLift,         tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          RIntake,       tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	bool trans;
	trans = false;
	SensorValue[Shift] = 0;
	while(true)
	{
		if(trans == false)
		{
			motor[LTrans] = vexRT[Ch3];
			motor[FLBase] = vexRT[Ch3];
			motor[BLBase] = vexRT[Ch3];
	 		motor[RTrans] = vexRT[Ch2];
	 		motor[FRBase] = vexRT[Ch2];
	 		motor[BRBase] = vexRT[Ch2];
	 		if(vexRT[Btn5D] == 1)
	 		{
	 			motor[LLift] = 100;
	 			motor[RLift] = 100;
	 		}
	 		else if(vexRT[Btn5U] == 1)
	 		{
	 			motor[LLift] = -100;
	 			motor[RLift] = -100;
	 		}
	 		else
	 		{
	 			motor[LLift] = 0;
	 			motor[RLift] = 0;
	 		}
	 		if(vexRT[Btn8U] == 1)
	 		{
	 			trans = true;
	 			SensorValue[Shift] = 1;
	 			motor[LTrans] = 127;
	 			motor[RTrans] = 127;
	 			wait10Msec(50);
	 		}
	 		if(vexRT[Btn8D] == 1)
	 		{
	 			trans = true;
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
	 		}
		}
		if(trans == true)
		{
			motor[FLBase] = vexRT[Ch3];
			motor[BLBase] = vexRT[Ch3];
	 		motor[FRBase] = vexRT[Ch2];
	 		motor[BRBase] = vexRT[Ch2];
	 		if(vexRT[Btn5D] == 1)
	 		{
	 			motor[LLift] = 100;
	 			motor[RLift] = 100;
	 			motor[LTrans] = -100;
	 			motor[RTrans] = -100;
	 		}
	 		if(vexRT[Btn5U] == 1)
	 		{
	 			motor[LLift] = -100;
	 			motor[RLift] = -100;
	 			motor[LTrans] = 100;
	 			motor[RTrans] = 100;
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
	 			trans = false;
	 			motor[LTrans] = 127;
	 			motor[RTrans] = 127;
	 			SensorValue[Shift] = 0;
	 			wait10Msec(50);
	 		}
	 		if(vexRT[Btn8D] == 1)
	 		{
	 			trans = false;
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
	 		}
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
	}


}
