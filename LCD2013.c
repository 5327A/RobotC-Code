task autonomous()						//All values must be adjusted due to the robot's change in weight and potentiometer values
{
	bLCDBacklight = false;		//Turns off LCD backlight

	clearLCDLine(0);
	clearLCDLine(1);

	//Switch Case that actually runs the user choice
	switch(count){
		case 0:									//If count = 0, run the code correspoinding with choice 1
			displayLCDCenteredString(0, "Mid Autonomous");
			displayLCDCenteredString(1, "is running!");
			lift(1450);
			down(50);
			intake(100);
			lift(1600);
			outtake(40);
			Sleep(600);
			forward(250, 127);
			lift(1000);
			forwardnstay(300, 60);
			staynouttake(50);
			backwardsnstay(250, 127);
			backwards(300, 127);
			Sleep(3000);
			forward(500, 127);
			lift(1000);
			forwardnstay(250, 60);
			backwardsnstay(250, 127);
			backwards(750, 127);
			break;
		case 1:									//If count = 1, run the code correspoinding with choice 2
			displayLCDCenteredString(0, "HR Autonomous");
			displayLCDCenteredString(1, "is running!");
			lift(1450);
			down(50);
			intake(100);
			forwardnintake(700,127);
			turnL(270, -270, 127);
			forward(25, 127);
			lift(1450);
			outtake(100);
			turnL(270, -270, 127);
			forward(270, 60);
			Sleep(2500);
			down(20);
			lift(1880);
			forwardnintake(480,127);
			intake(50);
			backwardsnintake(480, 127);
			Sleep(1500);
			lift(1000);
			forwardnstay(50, 127);
			outtake(200);
			break;
		case 2:								//If count = 2, run the code correspoinding with choice 3
			displayLCDCenteredString(0, "HB Autonomous");
			displayLCDCenteredString(1, "is running!");
			lift(1450);
			down(50);
			intake(100);
			forwardnintake(700,127);
			turnR(-270, 270, 127);
			lift(1450);
			outtake(100);
			turnR(-400, 400, 127);
			forward(250, 60);
			Sleep(2500);
			down(20);
			lift(1880);
			forwardnintake(480,127);
			intake(50);
			backwardsnintake(480, 127);
			Sleep(1500);
			lift(1000);
			forwardnstay(50, 127);
			outtake(200);
			break;
	}
}
