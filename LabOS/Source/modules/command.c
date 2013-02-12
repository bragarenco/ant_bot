/*
 * core.cpp
 *
 *  Created on: Mar 27, 2011
 *      Author: Andrey
 */

#include "command.h"

#if(USE_LAB_OS_COMMAND == 1)

static portTASK_FUNCTION( vCmdTask, pvParameters );

/*-----------------------------------------------------------*/
void vStartCmdTask( unsigned portBASE_TYPE cmdPriority){

	/* The Tx task is spawned with a lower priority than the Rx task. */
	xTaskCreate( vCmdTask, ( signed char * ) "Cmd", cmdSTACK_SIZE, NULL, cmdPriority, ( xTaskHandle * ) NULL );

}


/*-----------------------------------------------------------*/
static portTASK_FUNCTION( vCmdTask, pvParameters )
 {
	portTickType xTimeToWait = 0xFF;

	char ch;

	/* Just to stop compiler warnings. */
	(void) pvParameters;

	for (;;) {

		if( xKeyGetChar(&ch ) )
		{
			DisplayCmd(ch);
		}
	}

 }


#endif
