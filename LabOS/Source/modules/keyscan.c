

#include "keyscan.h"

#if(USE_LAB_OS_KEYPAD_4x4 == 1)

static portTASK_FUNCTION( vKeyScanTask, pvParameters );

/* The key task will block on the Key queue for a long period. */
#define keyBLOCK_TIME				( ( portTickType ) 0xff )
#define keyNO_BLOCK_TIME			( ( portTickType ) 0x00 )
static xQueueHandle xKeyCharQueue;
signed portBASE_TYPE xKeyPushChar(char cOutChar);


char KeyToChar(char key);

void KeyInit();
void KeyToIdleState();
char KeyPressed();
void KeyActivateColumn(char col_select);
char KeyGet();


/*-----------------------------------------------------------*/
void vStartKeyScanTask( unsigned portBASE_TYPE keyPriority, unsigned portBASE_TYPE uxQueueLength){

	// Init keyboard port
	KeyInit();

	/* Create the queues used by the key scanner task. */
	xKeyCharQueue = xQueueCreate( uxQueueLength, ( unsigned portBASE_TYPE ) sizeof( char ) );


	/* The Tx task is spawned with a lower priority than the Rx task. */
	xTaskCreate( vKeyScanTask, ( signed char * ) "KeyScan", keyscanSTACK_SIZE, NULL, keyPriority, ( xTaskHandle * ) NULL );


}

/*-----------------------------------------------------------*/
static portTASK_FUNCTION( vKeyScanTask, pvParameters )
 {

	portTickType xLastExecutionTime;
	portTickType xTimeToWait = 200 / portTICK_RATE_MS;

	/* Just to stop compiler warnings. */
	(void) pvParameters;

	/* Initialize the variable used by the call to vTaskDelayUntil(). */
	xLastExecutionTime = xTaskGetTickCount();

	for (;;) {

		// Turn Keyboard into Idle State
		KeyToIdleState();

		/* This is a periodic task. Block until it is time to run again.
		The task will execute every 200ms. */
		vTaskDelayUntil( &xLastExecutionTime, xTimeToWait );

		// detect a keypress
		if (KeyPressed()) {

			// keyboard scan
			for (unsigned char col_select = 0; col_select < 4; col_select++) {

				// enable the column
				KeyActivateColumn(col_select);

				// keep the scaner state
				vTaskDelay(xTimeToWait>>4);

				// detect the key press
				if (KeyPressed()) {

					// get the key
					char key = KeyGet();

					// Convert key to char
					char ch = KeyToChar(key);

					// TODO write in buffer if is not full
					xKeyPushChar(ch);


					break;
				}
			}
		}
	}
}

/*-----------------------------------------------------------*/
signed portBASE_TYPE xKeyPushChar(char cOutChar)
{

	/* Return false if after the block time there is no room on the Key queue. */
	if( xQueueSend( xKeyCharQueue, &cOutChar, keyBLOCK_TIME ) != pdPASS )
	{
		return pdFAIL;
	}

	return pdPASS;
}

/*-----------------------------------------------------------*/
signed portBASE_TYPE xKeyGetChar(char *pcRxedChar)
{

	/* Get the next character from the buffer.  Return false if no characters
	are available, or arrive before xBlockTime expires. */
	if( xQueueReceive( xKeyCharQueue, pcRxedChar, keyBLOCK_TIME ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}

/*-----------------------------------------------------------*/

char KeyToChar(char key){
	
	key=~key;

	switch(key){
		case 0x11: key = '1';
		break;
		case 0x12: key = '2';
		break;
		case 0x14: key = '3';
		break;
		case 0x18: key = 'u';
		break;
		case 0x21: key = '4';
		break;
		case 0x22: key = '5';
		break;
		case 0x24: key = '6';
		break;
		case 0x28: key = 'l';
		break;
		case 0x41: key = '7';
		break;
		case 0x42: key = '8';
		break;
		case 0x44: key = '9';
		break;
		case 0x48: key = 'r';
		break;
		case 0x81: key = '*';
		break;
		case 0x82: key = '0';
		break;
		case 0x84: key = '#';
		break;
		case 0x88: key = 'd';
		break;

		default:
			key = 0; //  ' ' - WS
	}
return key;
}
#endif
