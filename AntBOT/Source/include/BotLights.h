/*
 * AntBOTLights.h
 *
 *  Created on: Nov 25, 2012
 *      Author: Andrei
 */

#ifndef BOT_LIGHTS_H_
#define BOT_LIGHTS_H_

#include "AntBot.h"

#ifdef USE_BOT_LIGHTS

#include "task.h"

#ifndef mainLIGHTS_PRIORITY
#define mainLIGHTS_PRIORITY	( tskIDLE_PRIORITY + 1 )
#endif

#ifndef lightsSTACK_SIZE
#define lightsSTACK_SIZE		configMINIMAL_STACK_SIZE
#endif

void vStartLightsTask(unsigned portBASE_TYPE lightsPriority);


void LightAllOn();
void LightAllOff();
void LightFrontOn();
void LightFrontOff();
void LightBackOn();
void LightBackOff();
void LightAllBlinkOn();
void LightAllBlinkOff();
void LightLeftBlinkOn();
void LightLeftBlinkOff();
void LightRightBlinkOn();
void LightRightBlinkOff();


#endif

#endif /* BOT_LIGHTS_H_ */
