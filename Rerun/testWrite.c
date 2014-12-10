#include <FlashLib.h>

static char robotData[14988];
task main()
{
		int i;
    for(i=0;i<14988;i+= 6){
        robotData[i] = vexRT[Ch3];
        robotData[i+1] = vexRT[Ch2];
        robotData[i+2] = vexRT[Btn5U]*127;
        robotData[i+3] = vexRT[Btn5D]*127;
        robotData[i+4] = vexRT[Btn6U]*127;
        robotData[i+5] = vexRT[Btn6D]*127;
        wait1Msec(6);
    }

    RCFS_AddFile();
    }

}
