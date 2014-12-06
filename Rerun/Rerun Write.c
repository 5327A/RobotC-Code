#pragma config(Motor,  port1,           LIntake,       tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           FRBase,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           BRBase,        tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port4,           BLBase,        tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port5,           FLBase,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LLift,         tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port9,           RLift,         tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          RIntake,       tmotorVex393_HBridge, openLoop, encoderPort, I2C_4)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include <FlashLib.h>

static char robotData[14988];

task main()
{
	startTask(rerun);
	motor[FLBase] = vexRT(Ch3);
	motor[BLBase] = vexRT(Ch3);
	motor[FRBase] = vexRT(Ch2);
	motor[BRBase] = vexRT(Ch2);
	if(vexRT(Btn5U==1){
		motor[LLift] = 127;
		motor[RLift] = 127;
	}
	else if(vexRT(Btn5D==1){
		motor[LLift] = -127;
		motor[RLift] = -127;
	}
	if(vexRT(vexRT(Btn6U)==1){
		motor[LIntake] = 127;
		motor[RIntake] = 127;
	}
	else if(vexRT(Btn6D)==1){
		motor[LIntake] = -127;
		motor[RIntake] = -127;
	}
}

task rerun()
{
		int i;
    for(i=0;i<14988;i+= 6){
        robotData[i] = vexRT[Ch3];
        robotData[i+1] = vexRT[Ch2];
        robotData[i+2] = vexRT[Btn5U];
        robotData[i+3] = vexRT[Btn5D];
        robotData[i+4] = vexRT[Btn6U];
        robotData[i+5] = vexRT[Btn6D];
        wait1Msec(6);
    }

    if( RCFS_AddFile( robotData, 14988, "atad") == RCFS_ERROR ){
        writeDebugStreamLine("File write error");
    }

}
