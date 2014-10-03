#pragma config(Sensor, dgtl1,  Shift,          sensorDigitalOut)
#pragma config(Motor,  port1,           LIntake,       tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           FRBase,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           FLBase,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           BRBase,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           BLBase,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           RTrans,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           LTrans,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LLift,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           RLift,         tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          RIntake,       tmotorVex393_HBridge, openLoop)

//Motor control with speed and distance in future
void right(int speed){
	motor[FRBase] = speed;
	motor[BRBase] = speed;
}

void left(int speed){
	motor[FLBase] = speed;
	motor[BLBase] = speed;
}

task main()
{



}
