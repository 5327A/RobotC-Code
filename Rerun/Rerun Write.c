#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include <FlashLib.h>

static char robotData[14988];

task main()
{
    int i;

    bLCDBacklight = 0;

    for(i = 0;i<=3;i++){
    	wait1Msec(1000);
    	bLCDBacklight = 1;
    	wait1Msec(1000);
    	bLCDBacklight = 0;
  	}

 	 	bLCDBacklight = 1;

    for(i=0;i<14988;i+= 6){
        robotData[i] = vexRT[Ch3];
        robotData[i+1] = vexRT[Ch2];
        robotData[i+2] = vexRT[Btn5U];
        robotData[i+3] = vexRT[Btn5D];
        robotData[i+4] = vexRT[Btn6U];
        robotData[i+5] = vexRT[Btn6D];
        wait1Msec(6);
    }

		bLCDBacklight = 0;

    if( RCFS_AddFile( robotData, 14988, "robotData" ) == RCFS_ERROR ){
        writeDebugStreamLine("File write error");
    }

}