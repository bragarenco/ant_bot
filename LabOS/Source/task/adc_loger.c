/*
 * core.cpp
 *
 *  Created on: Mar 27, 2011
 *      Author: Andrey
 */

#include "adc_loger.h"
#include "adc.h"
#include "keyscan.h"
#include "resources.h"
#include "display8x7seg.h"



#if(USE_LAB_OS_ADC_LOG == 1)

#define adcSTACK_SIZE	configMINIMAL_STACK_SIZE

static portTASK_FUNCTION( vAdcLogTask, pvParameters );


/*-----------------------------------------------------------*/
void vStartAdcLogTask( unsigned portBASE_TYPE cmdPriority){

	vAdcInit(5);
	/* The Tx task is spawned with a lower priority than the Rx task. */
	xTaskCreate( vAdcLogTask, ( signed char * ) "AdcLog", adcSTACK_SIZE, NULL, cmdPriority, ( xTaskHandle * ) NULL );

}

char msg[10];
/*-----------------------------------------------------------*/
static portTASK_FUNCTION( vAdcLogTask, pvParameters )
 {
	portTickType xTimeToWait = 20;

	char ch;
	char chanel;

	/* Just to stop compiler warnings. */
	(void) pvParameters;


	for (;;) {

		vTaskDelay(xTimeToWait);

		if( xKeyGetChar(&ch ) )
		{
			chanel = ch-'0';
		}
		DisplayClear();
		StringAssign(msg,"Ch");
		StringPushBack(msg,ch);
		StringPushBack(msg,'-');
		char strSize = StringSize(msg);
		int adcData = GetAdcData(chanel);
		intToStr(adcData, msg+strSize);
		displayPrint(msg);
	}

 }
#endif


