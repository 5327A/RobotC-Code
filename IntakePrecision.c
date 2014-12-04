int reset = 0;
int hookValues[5];
int fullRound = -3605;
int fallback = 0;
int CURRENT_SHIFT = 0;

void intakeTo(int IME_VALUE_DEST){
	if((nMotorEncoder[RIntake]-IME_VALUE_DEST)%3605<-1802){
		outtake(IME_VALUE_DEST, 127);
	}
	else{
		intake(IME_VALUE_DEST, 127);
	}
}

void shiftin(int ROTATION_DIRECTION){
	if(ROTATION_DIRECTION == 0){
		if(CURRENT_SHIFT == 0){
			CURRENT_SHIFT = 5;
		}
		CURRENT_SHIFT--;
		outtake(hookValues[CURRENT_SHIFT], 127);
	}
	else if(ROTATION_DIRECTION == 1){
		if(CURRENT_SHIFT == 4){
			CURRENT_SHIFT = -1;
		}
		CURRENT_SHIFT++;
		intake(hookValues[CURRENT_SHIFT], 127);
	}
}

task main()
{
	hookValues[0] = 0;
	hookValues[1] = -724;
	hookValues[2] = -1501;
	hookValues[3] = -2237;
	hookValues[4] = -3008;
	while(true){
		if(vexRT[Btn8U] == 1){
			shiftin(1);
		}
		else if(vexRT[Btn8D] == 1){
			shiftin(0);
		}
		else if(vexRT[Btn8R] == 1){
			intakeTo(hookValues[0]);
		}
		else if(vexRT[Btn8L] == 1){
			intakeTo(hookValues[4]);
		}
	}
}
