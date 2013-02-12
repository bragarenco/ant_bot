/*
 * BotButton.h
 *
 *  Created on: Dec 18, 2012
 *      Author: Andrei
 */

#ifndef BOT_BUTTON_H_
#define BOT_BUTTON_H_

#include "AntBot.h"

#if(USE_BOT_BUTTON == 1)
#include "task.h"
#include "queue.h"

#ifndef mainBUTTON_PRIORITY
#define mainBUTTON_PRIORITY	( tskIDLE_PRIORITY + 1 )
#endif

#ifndef buttonSTACK_SIZE
#define buttonSTACK_SIZE		configMINIMAL_STACK_SIZE
#endif

#ifndef buttonBUFFER_LEN
#define	buttonBUFFER_LEN		8
#endif

#define BUTTON_1 1<< PIN_BUTTON_1
#define BUTTON_2 1<< PIN_BUTTON_2
#define BUTTON_3 1<< PIN_BUTTON_3
#define BUTTON_4 1<< PIN_BUTTON_4

void vStartButtonTask ( unsigned portBASE_TYPE buttonPriority,
						unsigned portBASE_TYPE uxQueueLength);
signed portBASE_TYPE xButtonGet(char *button);
void ButtonIOInit(void);
#endif
#endif /* BOT_BUTTON_H_ */
