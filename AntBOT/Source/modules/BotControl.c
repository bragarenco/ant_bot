/*
 * BotControl.c
 *
 *  Created on: Dec 21, 2012
 *      Author: Andrei
 */

#include "BotControl.h"

#if USE_BOT_CTRL == 1

#include "BotServo.h"
#include "BotButton.h"
#include "BotLights.h"
#include "BotPower.h"
#include "lcd.h"
#include "resources.h"

static portTASK_FUNCTION( vControlTask, pvParameters );

void vStartControlTask(unsigned portBASE_TYPE controlPriority) {

	/* The Tx task is spawned with a lower priority than the Rx task. */
	xTaskCreate( vControlTask, ( signed char * ) "BotCtrl", controlSTACK_SIZE, NULL, controlPriority, ( xTaskHandle * ) NULL );

}

char button;
int RC;
char numStr[6];


static portTASK_FUNCTION( vControlTask, pvParameters ) {

	portTickType xLastExecutionTime;
	portTickType xTimeToWait = 1000 / portTICK_RATE_MS; // ms

	char frontOn=0;
	char backOn=0;
	char LeftOn=0;
	char rightOn=0;
	/* Just to stop compiler warnings. */
	(void) pvParameters;

	/* Initialize the variable used by the call to vTaskDelayUntil(). */
	xLastExecutionTime = xTaskGetTickCount();





	for (;;) {
//		char* pButton = &button;
		/* This is a periodic task. Block until it is time to run again.
		 The task will execute every  xTimeToWait ms. */
//		vTaskDelayUntil(&xLastExecutionTime, xTimeToWait);


		if (xButtonGet(&button)!=pdFALSE) {


			if (button == BUTTON_1) {
				lcd_gotoxy(0,1);
				lcd_puts("BUTTON_1");
				RC_AddUnits(10,ARM_PIN);
				if(LeftOn^=0xFF) LightLeftBlinkOff();
				else 			 LightLeftBlinkOn();
			} else if (button == BUTTON_2) {
				lcd_gotoxy(0,1);
				lcd_puts("BUTTON_2");
				if(frontOn^=0xFF)LightFrontOff();
				else 			 LightFrontOn();
			} else if (button == BUTTON_3) {
				lcd_gotoxy(0,1);
				lcd_puts("BUTTON_3");
				if (backOn^=0xFF)LightBackOff();
				else 			 LightBackOn();
			} else if (button == BUTTON_4) {
				lcd_gotoxy(0,1);
				lcd_puts("BUTTON_4");
				RC_AddUnits(-10,ARM_PIN);
				if(rightOn^=0xFF) LightRightBlinkOff();
				else 			  LightRightBlinkOn();
			}
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

		}
//
//		if(currentServoPos >= RC_RES)
//			upDownFlag = 0;
//		if(currentServoPos <= 0)
//			upDownFlag = 1;
//
//		if(upDownFlag)
//			currentServoPos+=100;
//		else
//			currentServoPos-=100;
//
//		//while(RC_PinIsNotIdleState());
//
//		RC_SetUnits(currentServoPos,7);
//
		//taskYIELD();
	}

}

#endif
