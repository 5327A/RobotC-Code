#include <FlashLib.h>

static char robotData[14992];

task rerun()
{
    int i;

    bLCDBacklight = 0;

    for(i = 0;i<3;i++){
    	wait1Msec(1000);
    	bLCDBacklight = 1;
    	wait1Msec(1000);
    	bLCDBacklight = 0;
  	}

 	 	bLCDBacklight = 1;

    for(i=0;i<14992;i+= 4){
        robotData[i] = vexRT[Ch3];
        robotData[i+1] = vexRT[Ch2];
        robotData[i+2] = vexRT[Btn5U];
        robotData[i+3] = vexRT[Btn5D];
        robotData[i+4] = vexRT[Btn6U];
        robotData[i+5] = vexRT[Btn6D];
        wait1Msec(6);
    }

		bLCDBacklight = 0;

    if( RCFS_AddFile( robotData, 14992, "rerunData" ) == RCFS_ERROR ){
        writeDebugStreamLine("File write error");
    }

}
