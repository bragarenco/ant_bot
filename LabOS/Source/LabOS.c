/*
 * LabOS.c
 *
 *  Created on: Jun 13, 2011
 *      Author: Andrey
 */

#include "LabOS.h"

/* labs file headers*/
#include "serial.h"
#include "protocol.h"
#include "keyscan.h"
#include "display8x7seg.h"
#include "command.h"
#include "stepper.h"
#include "task/adc_loger.h"

void vStartLabOS(void){

#if(USE_LAB_OS_SERIAL == 1)
	//	char comBUFFER_LEN = 8;
	xSerialPortInitMinimal( mainCOM_TEST_BAUD_RATE, comBUFFER_LEN );
#endif

#if(USE_LAB_OS_PROTOCOL == 1)
	//	char comBUFFER_LEN = 8;
	vStartProtocolTask(mainCMD_PRIORITY);
#endif

#if(USE_LAB_OS_TERMINAL == 1)
	vStartTermTask( mainTERM_PRIORITY, mainCOM_TEST_BAUD_RATE, mainCOM_TEST_LED );
#endif

#if(USE_LAB_OS_COMMAND == 1)
	vStartCmdTask(mainCMD_PRIORITY);
	//	CommandPutChar('d');
#endif

#if(USE_LAB_OS_7_SEG_DISPLAY == 1)
	/* start Dysplay  8x7 segment */
	vStartDisplayTask(mainDISPLAY_PRIORITY);
#endif

#if(USE_LAB_OS_KEYPAD_4x4 == 1)
	/* start keyboard scaner task*/
	vStartKeyScanTask(mainKEY_PRIORITY, keyBUFFER_LEN);
#endif

#if(USE_LAB_OS_STEPPER == 1)
	/* start stepper task*/
	vStartStepperTask(mainSTEPPER_PRIORITY);
#endif

#if(USE_LAB_OS_ADC_LOG == 1)
	vStartAdcLogTask(mainADCLOG_PRIORITY);
#endif


}
