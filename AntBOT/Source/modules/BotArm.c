/*
 * BotArm.c
 *
 *  Created on: Dec 8, 2012
 *      Author: Andrei
 */

#include "BotArm.h"

#if USE_BOT_ARM == 1

#include "lcd.h"
#include "resources.h"
#include "BotServo.h"

static portTASK_FUNCTION( vArmTask, pvParameters );


void vStartArmTask(unsigned portBASE_TYPE armPriority) {

	/* The Tx task is spawned with a lower priority than the Rx task. */
	xTaskCreate( vArmTask, ( signed char * ) "BotArm", armSTACK_SIZE, NULL, armPriority, ( xTaskHandle * ) NULL );


}

int RC;
char numStr[6];
char upDownFlag = 1;
unsigned int currentServoPos = 0;

static portTASK_FUNCTION( vArmTask, pvParameters ) {

	portTickType xLastExecutionTime;
	portTickType xTimeToWait = 1000 / portTICK_RATE_MS; // ms

	/* Just to stop compiler warnings. */
	(void) pvParameters;

	/* Initialize the variable used by the call to vTaskDelayUntil(). */
	xLastExecutionTime = xTaskGetTickCount();

	for (;;) {


		if(currentServoPos >= RC_RES)
			upDownFlag = 0;
		if(currentServoPos <= 0)
			upDownFlag = 1;

		if(upDownFlag)
			currentServoPos+=100;
		else
			currentServoPos-=100;


		RC_SetUnits(currentServoPos,ARM_PIN);

			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts(" RC:");
			RC = RC_GetUnits(ARM_PIN);
			intToStr(RC,numStr);
			lcd_puts(numStr);

			lcd_gotoxy(0,1);
			lcd_puts("OCR:");
			RC = RC_GetOCR(ARM_PIN);
			intToStr(RC,numStr);
			lcd_puts(numStr);


		/* This is a periodic task. Block until it is time to run again.
		 The task will execute every  xTimeToWait ms. */
		vTaskDelayUntil(&xLastExecutionTime, xTimeToWait);
		//taskYIELD();
	}

}

#endif
