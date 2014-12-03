#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  Shift,          sensorDigitalOut)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           LIntake,       tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           FRBase,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           BRBase,        tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port4,           BLBase,        tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port5,           FLBase,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           RTrans,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           LTrans,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LLift,         tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port9,           RLift,         tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          RIntake,       tmotorVex393_HBridge, openLoop, encoderPort, I2C_4)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
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

//int total = 3588;
//int cl = -4507 + 3588 + 3588;
#define DRIVE_MAX       127			//Max/Min Speeds(PID)
#define DRIVE_MIN     (-127)

float  pid_Kp = 1.0; 	//P Control Var
int leftbtn = 1;			//LCD Left Button
int selectbtn = 2;		//LCD Select Button
int rightbtn = 4;			//LCD Right Button
int backbtn = 5;			//LCD Back Button
int resetbtn = 7;			//LCD Reset Button
int autonSelect = 0;	//LCD Autonomous Selecting Variable
//Main Screen Options Array
string mainScreen[4] = {"<- Autonomous ->", "<- Statistics ->", "<- Battery V. ->", "<-  Controls  ->"};
//Autonomous Select Screen Options Array
string autonScreen[8] = {"<-  RL1Auton  ->","<-  RL2Auton  ->", "<-  RR1Auton  ->", "<-  RR2Auton  ->", "<-  BL1Auton  ->", "<-  BL2Auton  ->", "<-  BR1Auton  ->", "<-  BR2Auton  ->"};
//Statistics/Sensor Values Screen Options Array
string statScreen[3] = {"<-  Base IME  ->", "<-  Lift IME  ->", "<- Intake IME ->"};
//Control Screen Options Array
string controlScreen[10] = {"<-  Forward   ->", "<-  Backward  ->", "<-  TurnLeft  ->", "<- TurnRight  ->", "<- SwingLeft  ->", "<- SwingRight ->", "<-    Lift    ->", "<-    Down    ->", "<-   Intake   ->", "<-  Outtake   ->"};
string primaryBattery;	//LCD Primary Battery String Parse Destination
string backupBattery;		//LCD Backup Battery String Parse Destination
string BLME;						//LCD Back Left Base IME String Parse Destination
string BRME;						//LCD Back Right Base IME String Parse Destination
string LLME;						//LCD Left Lift IME String Parse Destination
string RIME;						//LCD Right Intake IME String Parse Destination

float pidL(int WantedVal)
{
    float Error;
    float Speed;

    Error      = 0;
    Speed 		 = 0;

    // calculate error
    Error = WantedVal - abs(nMotorEncoder[BLBase]);

    // integral - if Ki is not 0
    // If we are inside controlable window then integrate the error
    // calculate drive
    Speed = (pid_Kp * Error);

    // limit drive
    if( Speed > DRIVE_MAX )
        Speed = DRIVE_MAX;
    if( Speed < DRIVE_MIN )
        Speed = DRIVE_MIN;

 		return Speed; //Send to motor
}

float pidR(int WantedVal)
{
    float Error;
    float Speed;

    Error      = 0;
    Speed 		 = 0;

    // calculate error
    Error = WantedVal - abs(nMotorEncoder[BRBase]);

    // integral - if Ki is not 0
    // If we are inside controlable window then integrate the error
    // calculate drive
    Speed = (pid_Kp * Error);

    // limit drive
    if( Speed > DRIVE_MAX )
        Speed = DRIVE_MAX;
    if( Speed < DRIVE_MIN )
        Speed = DRIVE_MIN;

 		return Speed; //Send to motor
}

void clearAllLCD(){ 					//Clears LCD Screen
	clearLCDLine(0);
	clearLCDLine(1);
}

void displayScreen(const string display){	//Standard Display screen format for LCD
	displayLCDString(0,0, display);
	displayLCDCenteredString(1,"<Select>");
}

void clearAllMotorEn(){				//Resets all Motor encoder values to 0
	nMotorEncoder[BLBase] = 0;
	nMotorEncoder[BRBase] = 0;
	nMotorEncoder[LLift] = 0;
	nMotorEncoder[RIntake] = 0;
}

void clear(){									//Clears all values and resets them to 0(Motors and Encoders)
	nMotorEncoder[BLBase] = 0;
	nMotorEncoder[BRBase] = 0;
	nMotorEncoder[RIntake] = 0;
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

void Pright(int speed, int distance){				//Power right side base motors
	motor[FRBase] = pidR(distance) * speed;
	motor[BRBase] = pidR(distance) * speed;
}

void Pleft(int speed, int distance){					//Power left side base motors
	motor[FLBase] = pidL(distance) * speed;
	motor[BLBase] = pidL(distance) * speed;
}

void Pforward(int distance, int speed){		//Move Forward
	while(nMotorEncoder[BLBase] < distance && nMotorEncoder[BRBase] > -distance){
		Pright(1, distance);
		Pleft(1, distance);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

void Pbackward(int distance, int speed){		//Move Backwards
	while(nMotorEncoder[BLBase] > -distance && nMotorEncoder[BRBase] < distance){
			Pright(-1, distance);
			Pleft(-1, distance);
		}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

void PturnRight(int distance, int speed){	//Turn Right
	while(nMotorEncoder[BLBase] < distance && nMotorEncoder[BRBase] < distance){
		Pright(-1, distance);
		Pleft(1, distance);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

void PturnLeft(int distance, int speed){		//Turn Left
	while(nMotorEncoder[BLBase] > -distance && nMotorEncoder[BRBase] > -distance){
		Pleft(-1, distance);
		Pright(1, distance);
	}
	motor[FRBase] = 0;
	motor[BRBase] = 0;
	motor[FLBase] = 0;
	motor[BLBase] = 0;
}

void right(int speed	){				//Power right side base motors
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

void outtake(int rotation, int speed){					//Intake/Outtake
	while(nMotorEncoder[RIntake] < rotation){
	motor[LIntake] = -speed;
	motor[RIntake] = -speed;
	}
	motor[LIntake] = 0;
	motor[RIntake] = 0;
}

void intake(int rotation, int speed){					//Intake/Outtake
	while(nMotorEncoder[RIntake] > -rotation){
	motor[LIntake] = speed;
	motor[RIntake] = speed;
	}
	motor[LIntake] = 0;
	motor[RIntake] = 0;
}

void transmission(){											//Change transmission mode
	if(SensorValue[Shift] == 0)
		SensorValue[Shift] = 1;
	else if(SensorValue[Shift] == 1)
		SensorValue[Shift] = 0;
}

task lcd()
{
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
	bLCDBacklight = true; //Turns on backlight
	int upperLim = 0;
	int x = 0;						//LCD Main Screen Hierarchy
	int y = 0;						//LCD Second Screen Hierarchy
	int z = 0;						//LCD Third Screen Hierarchy
	while(true){
		clearAllLCD();
		if(y == 0){					//LCD Main Screen
			x = 0;
			while(y == 0){
				displayScreen(mainScreen[x]);
				if(nLCDButtons == leftbtn){
					x--;
				}
				else if(nLCDButtons == rightbtn){
					x++;
				}
				else if(nLCDButtons == selectbtn){
					y++;
				}
				else if(nLCDButtons == resetbtn){
					y = 0;
				}

				if(x < 0){
					x = 3;
				}
				else if(x > 3){
					x = 0;
				}
				wait1Msec(125);
			}
		}
		else if(y == 1 && x == 0){	//LCD Autonomous Screen
			z = 0;
			while(y == 1){
				displayScreen(autonScreen[z]);
				upperLim = 7;
				if(nLCDButtons == leftbtn){
					z--;
				}
				else if(nLCDButtons == rightbtn){
					z++;
				}
				else if(nLCDButtons == selectbtn){
					autonSelect = z;
					y++;
					displayLCDCenteredString(0, "Autonomous");
					displayLCDCenteredString(1, "Selected");
				}
				else if(nLCDButtons == backbtn){
					y--;
				}
				else if(nLCDButtons == resetbtn){
					y = 0;
				}

				if(z < 0){
					z = upperLim;
				}
				else if(z > upperLim){
					z = 0;
				}
				wait1Msec(125);
			}
		}
		else if(y == 1 && x == 1){	//LCD Statistics/Sensor Value Screen
			z = 0;
			while(y == 1){
				displayScreen(statScreen[z]);
				upperLim = 2;
				if(nLCDButtons == leftbtn){
					z--;
				}
				else if(nLCDButtons == rightbtn){
					z++;
				}
				else if(nLCDButtons == selectbtn){
					y++;
				}
				else if(nLCDButtons == backbtn){
					y--;
				}
				else if(nLCDButtons == resetbtn){
					y = 0;
				}

				if(z < 0){
					z = upperLim;
				}
				else if(z > upperLim){
					z = 0;
				}
				wait1Msec(125);
			}
		}
		else if(y == 1 && x == 2){	//LCD Battery Voltage Screen
			z = 0;
			while(y == 1){
				displayLCDString(0,0, "Primary:");
				displayLCDString(1,0, "Backup:");
				sprintf(primaryBattery, "%1.4f%c", nImmediateBatteryLevel/1000.0000,'V');
				sprintf(backupBattery, "%1.4f%c", BackupBatteryLevel/1000.0000,'V');
				displayLCDString(0,9, primaryBattery);
				displayLCDString(1,9, backupBattery);
				upperLim = 0;
				if(nLCDButtons == resetbtn){
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					y--;
				}
				wait1Msec(125);
			}
		}
		else if(y == 1 && x == 3 ){	//LCD Control Screen
			z = 0;
			while(y == 1){
				displayScreen(controlScreen[z]);
				upperLim = 9;
				if(nLCDButtons == leftbtn){
					z--;
				}
				else if(nLCDButtons == rightbtn){
					z++;
				}
				else if(nLCDButtons == selectbtn){
					y++;
				}
				else if(nLCDButtons == backbtn){
					y--;
				}
				else if(nLCDButtons == resetbtn){
					y = 0;
				}

				if(z < 0){
					z = upperLim;
				}
				else if(z > upperLim){
					z = 0;
				}
				wait1Msec(125);
			}
		}
		else if(y == 2 && x == 1 && z == 0){	//LCD Base IME Value Screen
			z = 0;
			while(y == 2){
				if(nLCDButtons == selectbtn){
					clearAllMotorEn();
				}
				displayLCDString(0,0, "BLBase:");
				displayLCDString(1,0, "BRBase:");
				sprintf(BLME, "%.2f%c", nMotorEncoder[BLBase]);
				sprintf(BRME, "%.2f%c", nMotorEncoder[BRBase]);
				displayLCDString(0,10, BLME);
				displayLCDString(1,10, BRME);
				upperLim = 0;
				if(nLCDButtons == resetbtn){
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					y--;
				}
				wait1Msec(125);
			}
		}
		else if(y == 2 && x == 1 && z == 1){	//LCD Lift IME Screen
			z = 0;
			while(y == 2){
				if(nLCDButtons == selectbtn){
					clearAllMotorEn();
				}
				displayLCDString(0,0, "LLift:");
				sprintf(LLME, "%.2f%c", nMotorEncoder[LLift]);
				displayLCDString(0,10, LLME);
				upperLim = 0;
				if(nLCDButtons == resetbtn){
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					y--;
				}
				wait1Msec(125);
			}
		}
		else if(y == 2 && x == 1 && z == 2){	//LCD Intake IME Screen
			z = 0;
			while(y == 2){
				if(nLCDButtons == selectbtn){
					clearAllMotorEn();
				}
				displayLCDString(0,0, "RIntake:");
				sprintf(RIME, "%.2f%c", nMotorEncoder[RIntake]);
				displayLCDString(0,10, RIME);
				upperLim = 0;
				if(nLCDButtons == resetbtn){
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					y--;
				}
				wait1Msec(125);
			}
		}
		else if(y == 2 && x == 3 && z == 0){	//LCD Forward Screen
			z = 0;
			forward(100,127);
			if(motor[BLBase] == 0){
				clearAllLCD();
				displayLCDCenteredString(0, "Done");
			}
			while(y == 2){
				if(nLCDButtons == resetbtn){
					forward(0,0);
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					forward(0,0);
					y--;
				}
			}
		}
		else if(y == 2 && x == 3 && z == 1){	//LCD Backward Screen
			z = 0;
			backward(100,127);
			if(motor[BLBase] == 0){
				clearAllLCD();
				displayLCDCenteredString(0, "Done");
			}
			while(y == 2){
				if(nLCDButtons == resetbtn){
					backward(0,0);
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					backward(0,0);
					y--;
				}
			}
		}
		else if(y == 2 && x == 3 && z == 2){	//LCD Turn Left Screen
			z = 0;
			turnLeft(100,127);
			if(motor[BLBase] == 0){
				clearAllLCD();
				displayLCDCenteredString(0, "Done");
			}
			while(y == 2){
				if(nLCDButtons == resetbtn){
					turnLeft(0,0);
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					turnLeft(0,0);
					y--;
				}
			}
		}
		else if(y == 2 && x == 3 && z == 3){	//LCD Turn Right Screen
			z = 0;
			turnRight(100,127);
			if(motor[BLBase] == 0){
				clearAllLCD();
				displayLCDCenteredString(0, "Done");
			}
			while(y == 2){
				if(nLCDButtons == resetbtn){
					turnRight(0,0);
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					turnRight(0,0);
					y--;
				}
			}
		}
		else if(y == 2 && x == 3 && z == 4){	//LCD Swing Left Screen
			z = 0;
			swingLeft(100,127);
			if(motor[BRBase] == 0){
				clearAllLCD();
				displayLCDCenteredString(0, "Done");
			}
			while(y == 2){
				if(nLCDButtons == resetbtn){
					swingLeft(0,0);
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					swingLeft(0,0);
					y--;
				}
			}
		}
		else if(y == 2 && x == 3 && z == 5){	//LCD Swing Right Screen
			z = 0;
			swingRight(100,127);
			if(motor[BLBase] == 0){
				clearAllLCD();
				displayLCDCenteredString(0, "Done");
			}
			while(y == 2){
				if(nLCDButtons == resetbtn){
					swingRight(0,0);
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					swingRight(0,0);
					y--;
				}
			}
		}
		else if(y == 2 && x == 3 && z == 6){	//LCD Lift Screen
			z = 0;
			lift(700,127);
			if(motor[LLift] == 0){
				clearAllLCD();
				displayLCDCenteredString(0, "Done");
			}
			while(y == 2){
				if(nLCDButtons == resetbtn){
					lift(0,0);
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					lift(0,0);
					y--;
				}
			}
		}
		else if(y == 2 && x == 3 && z == 7){	//LCD Down Screen
			z = 0;
			down(700,127);
			if(motor[LLift] == 0){
				clearAllLCD();
				displayLCDCenteredString(0, "Done");
			}
			while(y == 2){
				if(nLCDButtons == resetbtn){
					down(0,0);
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					down(0,0);
					y--;
				}
			}
		}
		else if(y == 2 && x == 3 && z == 8){	//LCD Intake Screen
			z = 0;
			intake(500,127);
			if(motor[RIntake] == 0){
				clearAllLCD();
				displayLCDCenteredString(0, "Done");
			}
			while(y == 2){
				if(nLCDButtons == resetbtn){
					intake(0,0);
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					intake(0,0);
					y--;
				}
			}
		}
		else if(y == 2 && x == 3 && z == 9){	//LCD Outtake Screen
			z = 0;
			intake(500, -127);
			if(motor[RIntake] == 0){
				clearAllLCD();
				displayLCDCenteredString(0, "Done");
			}
			while(y == 2){
				if(nLCDButtons == resetbtn){
					intake(0,0);
					y = 0;
				}
				else if(nLCDButtons == backbtn){
					intake(0,0);
					y--;
				}
			}
		}
		if(nLCDButtons == resetbtn){
			y = 0;
		}
		wait1Msec(125);
	}

}


void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	nMotorEncoder[RIntake] = nMotorEncoder[RIntake] + 3588 + 3588;
	startTask(lcd);
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*
task reset()
{
	while(nMotorEncoder[RIntake]%total < 0%total)
	{
		motor[LIntake] = -127;
		motor[RIntake] = -127;
	}
	motor[LIntake] = 0;
	motor[RIntake] = 0;
}

task next()
{
	while(nMotorEncoder[RIntake] < nMotorEncoder[RIntake] + 700)
	{
		motor[LIntake] = 127;
		motor[RIntake] = 127;
	}
	motor[LIntake] = 0;
	motor[RIntake] = 0;
}

task claw()
{
	while(nMotorEncoder[RIntake]%total < cl%total)
	{
		motor[LIntake] = -127;
		motor[RIntake] = -127;
	}
	motor[LIntake] = 0;
	motor[RIntake] = 0;
}
*/

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
	backward(100, 127);
	clear();
	clear();
	lift(370, 127);
	//down(10, 60);
	clear();
	outtake(800, 70);
	clear();

	//Move Towards Cube and Intake Cube
	forward(240, 50);
	Sleep(500);
  clear();
  lift(700, 127);
  clear();
  backward(50, 50);
  clear();
  turnLeft(300, 50);
  clear();
  forward(10, 30);
  clear();
  intake(10,40);
  down(100,70);
  clear();
  backward(20 ,30);
  clear();
  lift(300, 70);
  clear();
  outtake(500, 127);
  clear();
  backward(100, 127);
  /*
  //Setup Approach Angle for Outtaking Cube
  turnLeft(50, 70);
  Sleep(50);
  forward(500, 70);
  clear();
  Sleep(50);

  //Lift and Intake so that Cubes are in Tray and in a Position Ready to Outtake
  lift(1380, 80);
  intake(40, 127);
  Sleep(60);
  clear();

  //Set up Outtaking Angle and Position
  turnRight(340 ,70);
  clear();
  Sleep(100);
  forward(120, 50);
  clear();
  //swingRight(50, 50);
  clear();
	*/
  //Outtake Cubes
  //backward(500, 127);

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
	int lift = 2;											//Highest height avalible from start
	int cube = 100;										//Autotap
	int small = 700;									//Small goal
	int medium = 1480;								//Medium Goal
	int large = 1230;									//High Goal
	int intakerise = 280;							//Skyrise Intake
	bool autotap = 0;
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
	 		if(vexRT[Btn5U] == 1)					//Lift Up, Max Height Depending on Lift Height Value
	 		{
	 			if(lift == 0)
	 			{
	 				if(nMotorEncoder[LLift] < cube)
	 				{
	 					motor[LLift] = 127;
	 					motor[RLift] = 127;
	 				}
	 				else
	 				{
	 					motor[LLift] = 10;
	 					motor[RLift] = 10;
	 				}
	 			}
	 			else if(lift == 1)
	 			{
	 				if(nMotorEncoder[LLift] < small)
	 				{
	 					motor[LLift] = 127;
	 					motor[RLift] = 127;
	 				}
	 				else
	 				{
	 					motor[LLift] = 10;
	 					motor[RLift] = 10;
	 				}
	 			}
	 			else if(lift == 2)
	 			{
	 				if(nMotorEncoder[LLift] < medium)
	 				{
	 					motor[LLift] = 127;
	 					motor[RLift] = 127;
	 				}
	 				else
	 				{
	 					motor[LLift] = 10;
	 					motor[RLift] = 10;
	 				}
	 			}
	 			else if(lift == 3)
	 			{
	 				if(nMotorEncoder[LLift] < large)
	 				{
	 					motor[LLift] = 127;
	 					motor[RLift] = 127;
	 				}
	 				else
	 				{
	 					motor[LLift] = 10;
	 					motor[RLift] = 10;
	 				}
	 			}
	 		}
	 		else if(vexRT[Btn7U] == 1)
	 		{
	 				if(nMotorEncoder[LLift] < intakerise)
	 				{
	 					motor[LLift] = 127;
	 					motor[RLift] = 127;
	 				}
	 				else
	 				{
	 					motor[LLift] = 0;
	 					motor[RLift] = 0;
	 				}
	 		}
	 		else if(vexRT[Btn5D] == 1)		//Retract Lift Down
	 		{
	 			motor[LLift] = -127;
	 			motor[RLift] = -127;
	 		}
	 		else if(vexRT[Btn5DXmtr2] == 1)		//Retract Lift Down
	 		{
	 			motor[LLift] = -40;
	 			motor[RLift] = -40;
	 		}
	 		else if(nMotorEncoder[LLift] < cube) 	//Autotap
	 		{
	 			motor[LLift] = 60;
	 			motor[RLift] = 60;
	 		}
	 		else
	 		{
	 			motor[LLift] = 0;
	 			motor[RLift] = 0;
	 		}
	 		if(vexRT[Btn8U] == 1)					//Shift to 4 Motor Base
	 		{
	 			SensorValue[Shift] = 0;
	 			bLCDBacklight = 1;
	 			wait10Msec(50);
	 		}

		}																//4 Motor Base Mode
		if(SensorValue[Shift] == 0)
		{
			motor[FLBase] = vexRT[Ch3];
			motor[BLBase] = vexRT[Ch3];
	 		motor[FRBase] = vexRT[Ch2];
	 		motor[BRBase] = vexRT[Ch2];
	 		if(vexRT[Btn5U] == 1)					//Lift Up
	 		{
	 			if(lift == 0)
	 			{
	 				if(nMotorEncoder[LLift] < cube)
	 				{
	 					motor[LLift] = 127;
	 					motor[RLift] = 127;
	 					motor[LTrans] = 127;
	 					motor[RTrans] = 127;
	 				}
	 				else
	 				{
	 					motor[LLift] = 10;
	 					motor[RLift] = 10;
	 					motor[LTrans] = 10;
	 					motor[RTrans] = 10;
	 				}
	 			}
	 			else if(lift == 1)
	 			{
	 				if(nMotorEncoder[LLift] < small)
	 				{
	 					motor[LLift] = 127;
	 					motor[RLift] = 127;
	 					motor[LTrans] = 127;
	 					motor[RTrans] = 127;
	 				}
	 				else
	 				{
	 					motor[LLift] = 10;
	 					motor[RLift] = 10;
	 					motor[LTrans] = 10;
	 					motor[RTrans] = 10;
	 				}
	 			}
	 			else if(lift == 2)
	 			{
	 				if(nMotorEncoder[LLift] < medium)
	 				{
	 					motor[LLift] = 127;
	 					motor[RLift] = 127;
	 					motor[LTrans] = 127;
	 					motor[RTrans] = 127;
	 				}
	 				else
	 				{
	 					motor[LLift] = 10;
	 					motor[RLift] = 10;
	 					motor[LTrans] = 10;
	 					motor[RTrans] = 10;
	 				}
	 			}
	 			else if(lift == 3)
	 			{
	 				if(nMotorEncoder[LLift] < large)
	 				{
	 					motor[LLift] = 127;
	 					motor[RLift] = 127;
	 					motor[LTrans] = 127;
	 					motor[RTrans] = 127;
	 				}
	 				else
	 				{
	 					motor[LLift] = 10;
	 					motor[RLift] = 10;
	 					motor[LTrans] = 10;
	 					motor[RTrans] = 10;
	 				}
	 			}
	 		}
	 		else if(vexRT[Btn7U] == 1)
			{
	 				if(nMotorEncoder[LLift] < intakerise)
	 				{
	 					motor[LLift] = 127;
	 					motor[RLift] = 127;
	 					motor[LTrans] = 127;
	 					motor[RTrans] = 127;
	 				}
	 				else
	 				{
	 					motor[LLift] = 10;
	 					motor[RLift] = 10;
	 					motor[LTrans] = 10;
	 					motor[RTrans] = 10;
	 				}

	 		}
	 		else if(vexRT[Btn5D] == 1)			//Retract Lift Downwards
	 		{
	 			motor[LLift] = -127;
	 			motor[RLift] = -127;
	 			motor[LTrans] = -127;
	 			motor[RTrans] = -127;
	 		}
	 		else if(vexRT[Btn5DXmtr2] == 1)		//Retract Lift Down
	 		{
	 			motor[LLift] = -40;
	 			motor[RLift] = -40;
	 			motor[LTrans] = -40;
	 			motor[RTrans] = -40;
	 		}
	 		else if(nMotorEncoder[LLift] < cube) 	//Autotap
	 		{
	 			if(autotap == 1)
	 			{
	 				motor[LLift] = 40;
	 				motor[RLift] = 40;
	 				motor[LTrans] = 40;
	 				motor[RTrans] = 40;
	 			}
	 			else if(autotap == 0)
	 			{
	 				motor[LLift] = 0;
	 				motor[RLift] = 0;
	 				motor[LTrans] = 0;
	 				motor[RTrans] = 0;
	 			}
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
	 			bLCDBacklight = 0;
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
		else if(vexRT[Btn6UXmtr2] == 1)				//Intake Reset
		{
			if(vexRT[Btn5UXmtr2] == 1)					//Slowdown
			{
				motor[LIntake] = 60;
				motor[RIntake] = 60;
			}
			else
			{
				motor[LIntake] = 127;
				motor[RIntake] = 127;
			}
		}
		else if(vexRT[Btn6DXmtr2] == 1)				//Intake Reset
		{
			if(vexRT[Btn5UXmtr2] == 1)					//Slow Down
			{
				motor[LIntake] = -60;
				motor[RIntake] = -60;
			}
			else
			{
				motor[LIntake] = -127;
				motor[RIntake] = -127;
			}
		}
		else
		{
			motor[LIntake] = 0;
			motor[RIntake] = 0;
		}
		if(vexRT[Btn8DXmtr2] == 1)						//Lift Heights
		{
			lift = 0;
		}
		if(vexRT[Btn8LXmtr2] == 1)
		{
			lift = 1;
		}
		if(vexRT[Btn8UXmtr2] == 1)
		{
			lift = 2;
		}
		if(vexRT[Btn8RXmtr2] == 1)
		{
			lift = 3;
		}
		if(vexRT[Btn7UXmtr2] == 1)					//Turn Autotap On/Off
		{
			if(autotap == true)
				autotap = false;
			else if(autotap == false)
				autotap = true;
		}
		/*
		if(vexRT[Btn5DXmtr2] == 1)		//Reset
		{
			startTask(reset);
		}
		if(vexRT[Btn5UXmtr2] == 1)		//Next
		{
			startTask(next);
		}
		if(vexRT[Btn6UXmtr2] == 1)		//Claw
		{
			startTask(claw);
		}
		*/
		if(vexRT[Btn7L] == 1)
		{
			startTask(autonomous);
			stopTask(usercontrol);
		}
	}
}
