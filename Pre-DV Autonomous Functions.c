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

void clear(){
	SensorValue[encoder] = 0;
}

void right(int speed){
	motor[FRBase] = speed;
	motor[BRBase] = speed;
}

void left(int speed){
	motor[FLBase] = speed;
	motor[BLBase] = speed;
}

void forward(int speed, int distance){
	while(/*encoderValue < distance*/){
		right(speed);
		left(speed);
	}
}

void backward(int speed, int distance){
	while(/*abs(encoderValue) < distance*/){
			right(speed);
			left(speed);
		}
}

//For turns, adjust speed argument individually to allow distance travel
void turnRight(int speed, int direction){
	while(/*Motor Encoder Math < direction*/){
		right(speed);
		left(-speed);
	}
}

void turnRight(int speed, float distance){
	while(/*Some Other Motor Encoder Math < distance*/){
		right(speed);
		left(-speed);
	}
}

void turnLeft(int speed, int direction){
	while(/*Motor Encoder Math < direction*/){
		left(speed);
		right(-speed);
	}
}

void turnLeft(int speed, float distance){
	while(/*Some Other Motor Encoder Math < direction*/){
		left(speed);
		right(-speed);
	}
}

void swingRight(int speed, float distance){
	while(/*Some Other Motor Encoder Math < distance*/){
		right(speed/2);
		left(speed);
	}
}

void swingRight(int speed, int direction){
	while(/*Motor Encoder Math < direction*/){
		right(speed/2);
		left(speed);
	}
}

void swingLeft(int speed, int direction){
	while(/*Motor Encoder Math < direction*/){
		left(speed/2);
		right(speed);
	}
}

void swingLeft(int speed, float distance){
	while(/*Some Other Motor Encoder Math < distance*/){
		left(speed/2);
		right(speed);
	}
}

//Ray and Navu suggest only measuring angles for necessary heights
void lift(int speed, int height){
	while(/*height < pwrRegress(motorEncoderValue)*/){
		motor[RLift] = speed;
		motor[LLift] = speed;
}

void intake(int speed){
	motor[LIntake] = speed;
	motor[RIntake] = speed;
}

void transmission(){
}







