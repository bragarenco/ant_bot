
#ifdef GCC_MEGA_AVR
	/* EEPROM routines used only with the WinAVR compiler. */
	#include <avr/eeprom.h>
#endif

#include <avr/io.h>
/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
//#include "LabOS.h"
#include "AntBOT.h"


/* An address in the EEPROM used to count resets.  This is used to check that
the demo application is not unexpectedly resetting. */
#define mainRESET_COUNT_ADDRESS			( ( void * ) 0x50 )


/*
 * Called on boot to increment a count stored in the EEPROM.  This is used to
 * ensure the CPU does not reset unexpectedly.
 */
static void prvIncrementResetCount( void );

/*
 * The idle hook is used to scheduler co-routines.
 */
void vApplicationIdleHook( void );

/*-----------------------------------------------------------*/


int main( void )
{

//	prvIncrementResetCount();

	vStartAntBOT();

	/* In this port, to use preemptive scheduler define configUSE_PREEMPTION
	as 1 in portmacro.h.  To use the cooperative scheduler define
	configUSE_PREEMPTION as 0. */
	vTaskStartScheduler();

	return 0;
}

static void prvIncrementResetCount( void )
{
unsigned char ucCount;

	eeprom_read_block( &ucCount, mainRESET_COUNT_ADDRESS, sizeof( ucCount ) );
	ucCount++;
	eeprom_write_byte( mainRESET_COUNT_ADDRESS, ucCount );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	// todo hint I commented it
//	vCoRoutineSchedule();
}

