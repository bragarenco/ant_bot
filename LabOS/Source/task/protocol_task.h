/*
 * protocol_task.h
 *
 *  Created on: Jul 4, 2011
 *      Author: Andrey
 */

#ifndef PROTOCOL_TASK_H_
#define PROTOCOL_TASK_H_
#include "LabOS.h"

#if(USE_LAB_OS_PROTOCOL == 1)
#include "task.h"

void vStartProtocolTask( unsigned portBASE_TYPE cmdPriority);
#endif

#endif /* PROTOCOL_TASK_H_ */
