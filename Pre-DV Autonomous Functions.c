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

void clear(){
	nMotorEncoder[BLBase] = 0;
	nMotorEncoder[BRBase] = 0;
	nMotorEncoder[LLift] = 0;
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
	while(nMotorEncoder[BLBase] < distance && nMotorEncoder[BRBase] < distance){
		right(speed);
		left(speed);
	}
}

void backward(int speed, int distance){
	while(nMotorEncoder[BLBase] < -distance && nMotorEncoder[BRBase] < -distance){
			right(-speed);
			left(-speed);
		}
}

//For turns, adjust speed argument individually to allow distance travel
void turnRight(int speed, int direction){
	while(nMotorEncoder[BLBase] > distance && nMotorEncoder[BRBase] < -distance){
		right(speed);
		left(-speed);
	}
}

void turnLeft(int speed, int direction){
	while(nMotorEncoder[BLBase] < -distance && nMotorEncoder[BRBase] > distance){
		left(speed);
		right(-speed);
	}
}

void swingRight(int speed, int distance){
	while(nMotorEncoder[BLBase] > distance){
		right(speed/2);
		left(speed);
	}
}


void swingLeft(int speed, int direction){
	while(nMotorEncoder[BRBase] > distance){
		left(speed/2);
		right(speed);
	}
}

//Ray and Navu suggest only measuring angles for necessary heights
void lift(int speed, int height){
	while(height < nMotorEncoder[LLift]){
		motor[RLift] = speed;
		motor[LLift] = speed;
}

void intake(int speed){
	motor[LIntake] = speed;
	motor[RIntake] = speed;
}

void transmission(){
	if(SensorValue[Shift] = 0)
		SensorValue[Shift] = 1;
	else if(SensorValue[Shift] = 1)
		SensorValue[Shift] = 0;
}
