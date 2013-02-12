

#ifndef KEYSCAN_H
#define KEYSCAN_H
#include "LabOS.h"

#if(USE_LAB_OS_KEYPAD_4x4 == 1)
#include "task.h"
#include "queue.h"

#ifndef mainKEY_PRIORITY
#define mainKEY_PRIORITY	( tskIDLE_PRIORITY + 1 )
#endif
#ifndef keyscanSTACK_SIZE
#define keyscanSTACK_SIZE	configMINIMAL_STACK_SIZE
#endif
#ifndef keyBUFFER_LEN
#define	keyBUFFER_LEN		8
#endif

void vStartKeyScanTask( unsigned portBASE_TYPE keyPriority, unsigned portBASE_TYPE uxQueueLength);
signed portBASE_TYPE xKeyGetChar(char *pcRxedChar);

#endif
#endif
