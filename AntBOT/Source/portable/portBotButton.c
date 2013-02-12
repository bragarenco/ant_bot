/*
 * portBotButton.c
 *
 *  Created on: Dec 18, 2012
 *      Author: Andrei
 */

#include "BotButton.h"

#if(USE_BOT_BUTTON == 1)

void ButtonIOInit(void){
	BUTTON_DDR &= ~(1<< PIN_BUTTON_1 |1<< PIN_BUTTON_2 |1<< PIN_BUTTON_3 |1<< PIN_BUTTON_4);
	BUTTON_PORT |= (1<< PIN_BUTTON_1 |1<< PIN_BUTTON_2 |1<< PIN_BUTTON_3 |1<< PIN_BUTTON_4);
}

#endif
