#include <FlashLib.h>

static char robotData[1000];
task main()
{
		int i;
    for(i=0;i<1000;i++){
        robotData[i] = vexRT[Ch3];
        wait1Msec(10);
    }

    if( RCFS_AddFile( robotData, 1000, "ata") == RCFS_ERROR ){
        writeDebugStreamLine("File write error");
    }

}
