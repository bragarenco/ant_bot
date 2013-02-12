/*
 * command.h
 *
 *  Created on: Mar 27, 2011
 *      Author: Andrey
 */

#ifndef CMD_H_
#define CMD_H_
#include "LabOS.h"

#if(USE_LAB_OS_COMMAND == 1)
#include "task.h"

#ifndef mainCMD_PRIORITY
#define mainCMD_PRIORITY	( tskIDLE_PRIORITY + 1 )
#endif
#ifndef cmdSTACK_SIZE
#define cmdSTACK_SIZE		configMINIMAL_STACK_SIZE
#endif



void vStartCmdTask( unsigned portBASE_TYPE cmdPriority);
//char CommandPutChar(char ch);

#endif
#endif /* CMD_H_ */
