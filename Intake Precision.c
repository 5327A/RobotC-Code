int reset = 0;
int hookValues[5];
hookValues[0] = 0;
hookValues[1] = -724;
hookValues[2] = -1501;
hookValues[3] = -2237;
hookValues[4] = -3008;
int fallback = 0;

task main()
{
	while(true){
		if(vexRT[Btn6U] == 1){
			//add fallback
			motorEncoder[RIntake] = 0;
		}



}
