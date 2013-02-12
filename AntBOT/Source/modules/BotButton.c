/*
 * BotButton.c
 *
 *  Created on: Dec 18, 2012
 *      Author: Andrei
 */

#include "BotButton.h"

#if(USE_BOT_BUTTON == 1)

static portTASK_FUNCTION( vButtonTask, pvParameters );
signed portBASE_TYPE xButtonSend(char button);

static xQueueHandle xButtonQueue;

#define buttonBLOCK_TIME		( ( portTickType ) 0xff )
#define buttonNO_BLOCK_TIME		( ( portTickType ) 0x00 )
#define buttonTIME_OUT			( ( portTickType ) 100 )

#define ButtonPressed1() (~BUTTON_PIN & 1<<PIN_BUTTON_1)
#define ButtonPressed2() (~BUTTON_PIN & 1<<PIN_BUTTON_2)
#define ButtonPressed3() (~BUTTON_PIN & 1<<PIN_BUTTON_3)
#define ButtonPressed4() (~BUTTON_PIN & 1<<PIN_BUTTON_4)

#define GetButton()(ButtonPressed1()| \
					ButtonPressed2()| \
					ButtonPressed3()| \
					ButtonPressed4())


void vStartButtonTask ( unsigned portBASE_TYPE buttonPriority,
						unsigned portBASE_TYPE uxQueueLength) {

	ButtonIOInit();

	xButtonQueue = xQueueCreate( uxQueueLength, ( unsigned portBASE_TYPE ) sizeof( char ) );


	/* The Tx task is spawned with a lower priority than the Rx task. */
	xTaskCreate( vButtonTask, ( signed char * ) "BotBtn", buttonSTACK_SIZE, NULL, buttonPriority, ( xTaskHandle * ) NULL );


}


static portTASK_FUNCTION( vButtonTask, pvParameters ) {

//	portTickType xLastExecutionTime;
	portTickType xTimeToWait = 500 / portTICK_RATE_MS; // ms

	/* Just to stop compiler warnings. */
	(void) pvParameters;

	/* Initialize the variable used by the call to vTaskDelayUntil(). */
//	xLastExecutionTime = xTaskGetTickCount();


	for (;;) {
//		/* This is a periodic task. Block until it is time to run again.
//		The task will execute every 200ms. */
//		vTaskDelayUntil( &xLastExecutionTime, xTimeToWait );

		// check if any button pressed
		if(GetButton()){
			char button;
			// delay to detect if double button pressed
			vTaskDelay(50 / portTICK_RATE_MS);
			// get the button
			button = GetButton();
			// register button in the buton Buffer
			xButtonSend(button);
			// delay between pressings
			vTaskDelay(xTimeToWait);
		}else{
//			taskYIELD();
		}

	}
}


/*-----------------------------------------------------------*/
signed portBASE_TYPE xButtonSend(char button)
{

	/* Return false if after the block time there is no room on the Key queue. */
	if( xQueueSend( xButtonQueue, &button, buttonTIME_OUT ) != pdPASS )
	{
		return pdFAIL;
	}

	return pdPASS;
}

/*-----------------------------------------------------------*/
signed portBASE_TYPE xButtonGet(char *button)
{

	/* Get the next character from the buffer.  Return false if no characters
	are available, or arrive before xBlockTime expires. */
	if( xQueueReceive( xButtonQueue, button, buttonTIME_OUT ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}
#endif
