/*
 * BotPower.c
 *
 *  Created on: Dec 25, 2012
 *      Author: Andrei
 */
#include "BotPower.h"

void PowerOn(){
	POWER_ON_DDR |= (1<<POWER_ON_LINE);
	POWER_ON_PORT |= (1<<POWER_ON_LINE);
}
void PowerOff(){
	POWER_ON_DDR |= (1<<POWER_ON_LINE);
	POWER_ON_PORT &= ~(1<<POWER_ON_LINE);
}

