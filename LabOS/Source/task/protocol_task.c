/*
 * protocol_task.c
 *
 *  Created on: Jul 4, 2011
 *      Author: Andrey
 */

/*
 * core.cpp
 *
 *  Created on: Mar 27, 2011
 *      Author: Andrey
 */

#include "protocol_task.h"
#include "protocol.h"
#include "keyscan.h"
#include "resources.h"
#include "serial.h"

#if(USE_LAB_OS_PROTOCOL == 1)

/* Handle to the com port used by both tasks. */
static xComPortHandle xPort0 = NULL;


#define protocolSTACK_SIZE	configMINIMAL_STACK_SIZE*2

static portTASK_FUNCTION( vProtocolTask, pvParameters );


/*-----------------------------------------------------------*/
void vStartProtocolTask( unsigned portBASE_TYPE cmdPriority){

	//vProtocolInit(5);

	/* The Tx task is spawned with a lower priority than the Rx task. */
	xTaskCreate( vProtocolTask, ( signed char * ) "Protocol", protocolSTACK_SIZE, NULL, cmdPriority, ( xTaskHandle * ) NULL );

}


char txPack[PACK_LENGTH];
char rxPack[PACK_LENGTH];

/*-----------------------------------------------------------*/
static portTASK_FUNCTION( vProtocolTask, pvParameters )
 {
	portTickType xTimeToWait = 20;

	/* Just to stop compiler warnings. */
	(void) pvParameters;

	char chFromKey;


	for (;;) {

		vTaskDelay(xTimeToWait);

		// detect key
		if (xKeyGetChar(&chFromKey)) {

			// Data Preparing
			txPack[4]=chFromKey;
			for (char i=5; i<PACK_LENGTH-2; i++)
				txPack[i]=i;

			// sending data
			SendPack(txPack, xPort0);
			// receiving back the data
			GetPack(rxPack, xPort0, 1 );
			char ch = rxPack[4];

			DisplayClear();
			displayPrint("Ch-");
			DisplayPutChar(ch);

		}

	}
 }
#endif
