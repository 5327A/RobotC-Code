#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)

int leftbtn = 1;
int selectbtn = 2;
int rightbtn = 4;
int backbtn = 5;
int resetbtn = 7;
int autonSelect = 0;
string mainScreen[4] = {"<- Autonomous ->", "<- Statistics ->", "<- Battery V. ->", "<-  Controls  ->"};
string autonScreen[8] = {"<-  RL1Auton  ->","<-  RL2Auton  ->", "<-  RR1Auton  ->", "<-  RR2Auton  ->", "<-  BL1Auton  ->", "<-  BL2Auton  ->", "<-  BR1Auton  ->", "<-  BR2Auton  ->"};
string statScreen[3] = {"<-  Base IME  ->", "<-  Lift IME  ->", "<- Intake IME ->"};
string controlScreen[10] = {"<-  Forward   ->", "<-  Backward  ->", "<-  TurnLeft  ->", "<- TurnRight  ->", "<- SwingLeft  ->", "<- SwingRight ->", "<-    Lift    ->", "<-    Down    ->", "<-   Intake   ->", "<-  Outtake   ->"};
string primaryBattery;
string backupBattery;
string BLME;
string BRME;
string LLME;
string RIME;

void clearAllLCD(){
	clearLCDLine(0);
	clearLCDLine(1);
}

void displayScreen(const string display){
	displayLCDString(0,0, display)
	displayLCDCenteredString(1,"<Select>");
}

void clearAllMotorEn(){
	nMotorEncoder[BLBase] = 0;
	nMotorEncoder[BRBase] = 0;
	nMotorEncoder[LLift] = 0;
	nMotorEncoder[RIntake] = 0;
}

task main()
}
	bLCDBacklight = 1;
	int upperLim = 0;
	int x = 0;
	int y = 0;
	int z = 0;
	while(true){
		clearAllLCD();
		if(y == 0){
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
		else if(y == 1 && x == 0){
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
		else if(y == 1 && x == 1){
			z = 0;
			while(y == 1){
				displayScreen(statScreen[z];
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
		else if(y == 1 && x == 2){
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
		else if(y == 1 && x == 3 ){
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
		else if(y == 2 && x == 1 && z == 0){
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
		else if(y == 2 && x == 1 && z == 1){
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
		else if(y == 2 && x == 1 && z == 2){
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
		else if(y == 2 && x == 3 && z == 0){
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
		else if(y == 2 && x == 3 && z == 1){
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
		else if(y == 2 && x == 3 && z == 2){
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
		else if(y == 2 && x == 3 && z == 3){
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
		else if(y == 2 && x == 3 && z == 4){
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
		else if(y == 2 && x == 3 && z == 5){
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
		else if(y == 2 && x == 3 && z == 6){
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
		else if(y == 2 && x == 3 && z == 7){
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
		else if(y == 2 && x == 3 && z == 8){
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
		else if(y == 2 && x == 3 && z == 9){
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
