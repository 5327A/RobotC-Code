#include <FlashLib.h>

static char robotData[6000];
task main()
{
		int i;
    for(i=0;i<6000;i+= 4){
        robotData[i] = vexRT[Btn5U];
        robotData[i+1] = vexRT[Btn5D];
        robotData[i+2] = vexRT[Btn6U];
        robotData[i+3] = vexRT[Btn6D];
        wait1Msec(10);
    }

    if( RCFS_AddFile( robotData, 6000, "joshData") == RCFS_ERROR ){
        writeDebugStreamLine("File write error");
    }

}
