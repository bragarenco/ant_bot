/*
 * BotWheelCtrl.c
 *
 *  Created on: Dec 28, 2012
 *      Author: Andrei
 */


#include "BotWheelCtrl.h"

#if USE_BOT_WHEEL == 1

#include "lcd.h"
#include "resources.h"
#include "BotServo.h"

static portTASK_FUNCTION( vWheelTask, pvParameters );


void vStartWheelTask(unsigned portBASE_TYPE wheelPriority) {

	/* The Tx task is spawned with a lower priority than the Rx task. */
	xTaskCreate( vWheelTask, ( signed char * ) "BotWheel", wheelSTACK_SIZE, NULL, wheelPriority, ( xTaskHandle * ) NULL );


}

int RC;
char numStr[6];
char upDownFlag = 1;
unsigned int currentServoPos = 0;

#define MAX_SPEED_STATE 0
#define NORMAL_STATE	10
struct WheelCtrl{
	int maxSpeedFwd;
	int maxSpeedBwd;

}leftWheel,RightWheel;

unsigned int lastAdcLeft = 0;
unsigned int curAdcLeft = 0;
int difAdcLeft = 0;
int difRcLeft = 0;

unsigned char leftWheelState = MAX_SPEED_STATE;

static portTASK_FUNCTION( vWheelTask, pvParameters ) {

	portTickType xLastExecutionTime;
	portTickType xTimeToWait = 200 / portTICK_RATE_MS; // ms
	portTickType xTimeToWaitCalibrate = 1000 / portTICK_RATE_MS; // ms

	/* Just to stop compiler warnings. */
	(void) pvParameters;

	/* Initialize the variable used by the call to vTaskDelayUntil(). */
	xLastExecutionTime = xTaskGetTickCount();

	for (;;) {

		if(leftWheelState==MAX_SPEED_STATE){
			// rise speed fwd
			while(RC_GetUnits(WR_PIN)>0){
				vTaskDelayUntil(&xLastExecutionTime, xTimeToWaitCalibrate);
				RC_AddUnits(-100,WR_PIN);

				lcd_clrscr();
				lcd_gotoxy(0,0);
				lcd_puts("FWD:");
				intToStr(leftWheel.maxSpeedFwd,numStr);
				lcd_puts(numStr);

				lcd_gotoxy(0,1);
				lcd_puts("BWD:");
				intToStr(leftWheel.maxSpeedBwd,numStr);
				lcd_puts(numStr);

			}
			// measure max speed fwd
			for (int i = 0; i < 10; ++i) {

				/* This is a periodic task. Block until it is time to run again.
				 The task will execute every  xTimeToWait ms. */
				vTaskDelayUntil(&xLastExecutionTime, xTimeToWaitCalibrate);

				curAdcLeft = GetAdcData(WR_ADC);
//				if(curAdcLeft>500){
					leftWheel.maxSpeedFwd = lastAdcLeft - curAdcLeft;
					lastAdcLeft = curAdcLeft;
//				}

				lcd_clrscr();
				lcd_gotoxy(0,0);
				lcd_puts("ADC:");
				intToStr(leftWheel.maxSpeedFwd,numStr);
				lcd_puts(numStr);

				lcd_gotoxy(0,1);
				lcd_puts("OCR:");
				RC = RC_GetUnits(WR_PIN);
				intToStr(RC,numStr);
				lcd_puts(numStr);

			}
			// rise speed bwd
			while(RC_GetUnits(WR_PIN)<RC_RES){
				vTaskDelayUntil(&xLastExecutionTime, xTimeToWaitCalibrate);
				RC_AddUnits(100,WR_PIN);

				lcd_clrscr();
				lcd_gotoxy(0,0);
				lcd_puts("FWD:");
				intToStr(leftWheel.maxSpeedFwd,numStr);
				lcd_puts(numStr);

				lcd_gotoxy(0,1);
				lcd_puts("BWD:");
				intToStr(leftWheel.maxSpeedBwd,numStr);
				lcd_puts(numStr);

			}
			// measure max speed bwd
			for (int i = 0; i < 10; ++i) {

				/* This is a periodic task. Block until it is time to run again.
				 The task will execute every  xTimeToWait ms. */
				vTaskDelayUntil(&xLastExecutionTime, xTimeToWaitCalibrate);

				curAdcLeft = GetAdcData(WR_ADC);
//				if(curAdcLeft>500){
					leftWheel.maxSpeedBwd = lastAdcLeft - curAdcLeft;
					lastAdcLeft = curAdcLeft;
//				}
				lcd_clrscr();
				lcd_gotoxy(0,0);
				lcd_puts("ADC:");
				intToStr(leftWheel.maxSpeedBwd,numStr);
				lcd_puts(numStr);

				lcd_gotoxy(0,1);
				lcd_puts("OCR:");
				RC = RC_GetUnits(WR_PIN);
				intToStr(RC,numStr);
				lcd_puts(numStr);

			}

			//leftWheelState = NORMAL_STATE;
		}else{

			/* This is a periodic task. Block until it is time to run again.
			 The task will execute every  xTimeToWait ms. */
			vTaskDelayUntil(&xLastExecutionTime, xTimeToWait);
			//taskYIELD();
		if(currentServoPos >= RC_RES/2 + 200-100)
			upDownFlag = 0;
		if(currentServoPos <= RC_RES/2 - 200-100)
			upDownFlag = 1;

		if(upDownFlag)
			currentServoPos+=10;
		else
			currentServoPos-=10;


		RC_SetUnits(currentServoPos,WL_PIN);

			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("ADC:");
			RC = GetAdcData(0);
			intToStr(RC,numStr);
			lcd_puts(numStr);

			lcd_gotoxy(0,1);
			lcd_puts("OCR:");
			RC = RC_GetUnits(WL_PIN);
			intToStr(RC,numStr);
			lcd_puts(numStr);

		}
	}

}

#endif
