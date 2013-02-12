/*
 * portBotLights.c
 *
 *  Created on: Nov 28, 2012
 *      Author: Andrei
 */

#include "BotLights.h"

void LightsIOInit(){
	LIGHTS_DDR  |=   (1<<PIN_LF)|(1<<PIN_RF)|(1<<PIN_LB)|(1<<PIN_RB);
	LIGHTS_PORT &= ~((1<<PIN_LF)|(1<<PIN_RF)|(1<<PIN_LB)|(1<<PIN_RB));
}

void LightsOn(char mask){
	LIGHTS_PORT |= mask;
}

void LightsOff(char mask){
	LIGHTS_PORT &= ~mask;
}

void LightsToggle(char mask){
	LIGHTS_PORT ^= mask;
}
