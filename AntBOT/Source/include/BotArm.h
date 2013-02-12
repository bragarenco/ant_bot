/*
 * BotArm.h
 *
 *  Created on: Dec 8, 2012
 *      Author: Andrei
 */

#ifndef BOT_ARM_H_
#define BOT_ARM_H_
#include "AntBot.h"

#if USE_BOT_ARM == 1
#include "task.h"

#ifndef mainARM_PRIORITY
#define mainARM_PRIORITY	( tskIDLE_PRIORITY + 1 )
#endif

#ifndef armSTACK_SIZE
#define armSTACK_SIZE		configMINIMAL_STACK_SIZE
#endif

void vStartArmTask(unsigned portBASE_TYPE armPriority);


#endif

#endif /* BOTARM_H_ */
