/*
 * AntBOTLights.c
 *
 *  Created on: Nov 25, 2012
 *      Author: Andrei
 */

#include "BotLights.h"


#ifdef USE_BOT_LIGHTS

#define LEFT_FRONT		  0
#define LEFT_BACK		  1
#define RIGHT_FRONT		  2
#define RIGHT_BACK		  3
#define LEFT_FRONT_BLINK  4
#define LEFT_BACK_BLINK   5
#define RIGHT_FRONT_BLINK 6
#define RIGHT_BACK_BLINK  7


char lightsConfig;

void LightsConfigSet(char mask);
void LightsConfigClear(char mask);
void LightsConfigWrite(char mask);
char GetLightsConfig();
char GetLightMask(const char lightsConfig);
char GetBlinkMask(const char lightsConfig);


// portable
void LightsIOInit();
void LightsConfigInit();
void LightsOn(char mask);
void LightsOff(char mask);
void LightsToggle(char mask);


// AllOn, frontOn, backOn, leftBlink, rightBlink

struct LightsConfig{
	char allOn:1;
	char allBlink:1;
	char frontOn:1;
	char backOn:1;
	char leftBlink:1;
	char rightBlink:1;
}lights;

static portTASK_FUNCTION( vLightsTask, pvParameters );


void vStartLightsTask(unsigned portBASE_TYPE lightsPriority) {

	LightsConfigInit();
	LightsIOInit();


	/* The Tx task is spawned with a lower priority than the Rx task. */
	xTaskCreate( vLightsTask, ( signed char * ) "BotLights", lightsSTACK_SIZE, NULL, lightsPriority, ( xTaskHandle * ) NULL );


}

static portTASK_FUNCTION( vLightsTask, pvParameters ) {

	portTickType xLastExecutionTime;
	portTickType xTimeToWait = 500 / portTICK_RATE_MS; // ms

	/* Just to stop compiler warnings. */
	(void) pvParameters;

	/* Initialize the variable used by the call to vTaskDelayUntil(). */
	xLastExecutionTime = xTaskGetTickCount();


	LightsConfigWrite(0xFF);

	lights.allOn = 0;
	lights.allBlink = 0;
	lights.frontOn = 1;
	lights.backOn = 0;
	lights.leftBlink = 0;
	lights.rightBlink = 1;

	for (;;) {


		char lightMask = 0;
		char blinkMask = 0;

		// extract lightsConfig from
		// AllOn, frontOn, backOn, leftBlink, rightBlink
		//
		lightsConfig = GetLightsConfig();

		//collect Lights ON mask
		lightMask = GetLightMask(lightsConfig);

		//collect Lights BLINK mask
		blinkMask = GetBlinkMask(lightsConfig);

		// OFFed lights will not blink
		blinkMask &= lightMask;

		// reset lights
		LightsOff( 1<< PIN_LF | 1<< PIN_RF | 1<< PIN_LB | 1<< PIN_RB );
		// turn ON with a new configuration
		LightsOn( lightMask );
		// keep lights the first half of refresh period
		vTaskDelayUntil(&xLastExecutionTime, xTimeToWait);

		// turn OFF the BLINK lights for the second half of refresh period
		LightsToggle( blinkMask );

		/* This is a periodic task. Block until it is time to run again.
		 The task will execute every  xTimeToWait ms. */
		vTaskDelayUntil(&xLastExecutionTime, xTimeToWait);
//		taskYIELD();
	}

}


void LightAllOn(){
	lights.allOn = 1;
}
void LightAllOff(){
	lights.allOn = 0;
}
void LightFrontOn(){
	lights.frontOn = 1;
}
void LightFrontOff(){
	lights.frontOn = 0;
}
void LightBackOn(){
	lights.backOn = 1;
}
void LightBackOff(){
	lights.backOn = 0;
}
void LightAllBlinkOn(){
	lights.allBlink = 1;
}
void LightAllBlinkOff(){
	lights.allBlink = 0;
}
void LightLeftBlinkOn(){
	lights.leftBlink = 1;
}
void LightLeftBlinkOff(){
	lights.leftBlink = 0;
}
void LightRightBlinkOn(){
	lights.rightBlink = 1;
}
void LightRightBlinkOff(){
	lights.rightBlink = 0;
}

// Initialize the Lights Configuration
void LightsConfigInit(){
	lightsConfig = 0x00;// all off
}

void LightsConfigSet(char mask){
	lightsConfig |= mask;
}

void LightsConfigClear(char mask){
	lightsConfig &= ~mask;
}

void LightsConfigWrite(char mask){
	lightsConfig = mask;
}



char GetLightsConfig(){
	char lightsConfig = 0;

	if(lights.allOn){
		lightsConfig|= 1<<LEFT_FRONT;
		lightsConfig|= 1<<RIGHT_FRONT;
		lightsConfig|= 1<<LEFT_BACK;
		lightsConfig|= 1<<RIGHT_BACK;
	}
	if(lights.allBlink){
		lightsConfig|= 1<<LEFT_FRONT;
		lightsConfig|= 1<<RIGHT_FRONT;
		lightsConfig|= 1<<LEFT_BACK;
		lightsConfig|= 1<<RIGHT_BACK;
		lightsConfig|= 1<<LEFT_FRONT_BLINK;
		lightsConfig|= 1<<RIGHT_FRONT_BLINK;
		lightsConfig|= 1<<LEFT_BACK_BLINK;
		lightsConfig|= 1<<RIGHT_BACK_BLINK;
	}
	if(lights.frontOn){
		lightsConfig|= 1<<LEFT_FRONT;
		lightsConfig|= 1<<RIGHT_FRONT;
	}
	if(lights.backOn){
		lightsConfig|= 1<<LEFT_BACK;
		lightsConfig|= 1<<RIGHT_BACK;
	}
	if(lights.leftBlink){
		lightsConfig|= 1<<LEFT_FRONT;
		lightsConfig|= 1<<LEFT_BACK;
		lightsConfig|= 1<<LEFT_FRONT_BLINK;
		lightsConfig|= 1<<LEFT_BACK_BLINK;
	}
	if(lights.rightBlink){
		lightsConfig|= 1<<RIGHT_FRONT;
		lightsConfig|= 1<<RIGHT_BACK;
		lightsConfig|= 1<<RIGHT_FRONT_BLINK;
		lightsConfig|= 1<<RIGHT_BACK_BLINK;
	}


	return lightsConfig;
}

char GetLightMask(const char lightsConfig){
	char lightMask = 0;
	if(lightsConfig & 1<< LEFT_FRONT )
		lightMask |= 1<< PIN_LF;
	if(lightsConfig & 1<< RIGHT_FRONT )
		lightMask |= 1<< PIN_RF;
	if(lightsConfig & 1<< LEFT_BACK )
		lightMask |= 1<< PIN_LB;
	if(lightsConfig & 1<< RIGHT_BACK )
		lightMask |= 1<< PIN_RB;

	return lightMask;
}

char GetBlinkMask(const char lightsConfig){
	char blinkMask = 0;
	if(lightsConfig & 1<< LEFT_FRONT_BLINK )
		blinkMask |= 1<< PIN_LF;
	if(lightsConfig & 1<< RIGHT_FRONT_BLINK )
		blinkMask |= 1<< PIN_RF;
	if(lightsConfig & 1<< LEFT_BACK_BLINK )
		blinkMask |= 1<< PIN_LB;
	if(lightsConfig & 1<< RIGHT_BACK_BLINK )
		blinkMask |= 1<< PIN_RB;

	return blinkMask;

}

#endif

