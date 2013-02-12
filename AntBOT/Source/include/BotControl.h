/*
 * BotControl.h
 *
 *  Created on: Dec 21, 2012
 *      Author: Andrei
 */

#ifndef BOT_CONTROL_H_
#define BOT_CONTROL_H_

#include "AntBot.h"

#if USE_BOT_CTRL == 1
#include "task.h"

#ifndef mainCONTROL_PRIORITY
#define mainCONTROL_PRIORITY	( tskIDLE_PRIORITY + 1 )
#endif

#ifndef controlSTACK_SIZE
#define controlSTACK_SIZE		configMINIMAL_STACK_SIZE
#endif

void vStartControlTask(unsigned portBASE_TYPE controlPriority);


#endif


#endif /* BOTCONTROL_H_ */
