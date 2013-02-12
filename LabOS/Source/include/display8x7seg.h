
#ifndef DISPLAY_H
#define DISPLAY_H

/* Scheduler include files. */
#include "LabOS.h"

#if(USE_LAB_OS_7_SEG_DISPLAY == 1)
#include "task.h"

#ifndef mainDISPLAY_PRIORITY
#define mainDISPLAY_PRIORITY	( tskIDLE_PRIORITY + 1 )
#endif

#ifndef displaySTACK_SIZE
#define displaySTACK_SIZE		configMINIMAL_STACK_SIZE
#endif

#ifndef DISPLAY_MEM_SIZE
#define DISPLAY_MEM_SIZE		0x20
#endif

#ifndef DISPLAY_SIZE
#define DISPLAY_SIZE			8
#endif

extern char *tabRef;

enum{
	LEFT_CMD = 5,
	RIGHT_CMD,
	PGUP_CMD,
	PGDWN_CMD,
	DEL_CMD,
	CLR_CMD
};

void vStartDisplayTask(unsigned portBASE_TYPE displayPriority);

void DisplayClear();
char DisplayDeleteChar();
void DisplayPutChar(char key);
void displayPrint(char str[]);
void displayLeft(unsigned char pos);
void DisplayRight(unsigned char pos);
void displayGoToX(char pos);
void displayShowX(char pos);
void DisplayCmd(char cmd, char ch);

#endif
#endif
