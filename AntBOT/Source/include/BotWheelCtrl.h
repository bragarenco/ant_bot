/*
 * BotWheelCtrl.h
 *
 *  Created on: Dec 28, 2012
 *      Author: Andrei
 */

#ifndef BOT_WHEEL_CTRL_H_
#define BOT_WHEEL_CTRL_H_

#include "AntBOT.h"

#if USE_BOT_WHEEL == 1
#include "task.h"

#ifndef mainWHEEL_PRIORITY
#define mainWHEEL_PRIORITY	( tskIDLE_PRIORITY + 1 )
#endif

#ifndef wheelSTACK_SIZE
#define wheelSTACK_SIZE		configMINIMAL_STACK_SIZE
#endif

void vStartWheelTask(unsigned portBASE_TYPE wheelPriority);


#endif


#endif /* BOT_WHEEL_CTRL_H_ */
