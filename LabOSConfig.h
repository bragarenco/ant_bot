/*
    FreeRTOS V6.1.0 - Copyright (C) 2010 Real Time Engineers Ltd.

    *******  ********************************************************************
    *                                                                         *
    * If you are:                                                             *
    *                                                                         *
    *    + New to FreeRTOS,                                                   *
    *    + Wanting to learn FreeRTOS or multitasking in general quickly       *
    *    + Looking for basic training,                                        *
    *    + Wanting to improve your FreeRTOS skills and productivity           *
    *                                                                         *
    * then take a look at the FreeRTOS books - available as PDF or paperback  *
    *                                                                         *
    *        "Using the FreeRTOS Real Time Kernel - a Practical Guide"        *
    *                  http://www.FreeRTOS.org/Documentation                  *
    *                                                                         *
    * A pdf reference manual is also available.  Both are usually delivered   *
    * to your inbox within 20 minutes to two hours when purchased between 8am *
    * and 8pm GMT (although please allow up to 24 hours in case of            *
    * exceptional circumstances).  Thank you for your support!                *
    *                                                                         *
    ***************************************************************************
*/

#ifndef LABOS_CONFIG_H
#define LABOS_CONFIG_H

#include <avr/io.h>
/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

// 8x7seg display configuration
#define USE_LAB_OS_7_SEG_DISPLAY	0
#define displayCHAR_PORT			PORTD
#define displayCHAR_DDR				DDRD
#define displaySELECT_PORT			PORTC
#define displaySELECT_DDR			DDRC

// Keyboard configuration
#define USE_LAB_OS_KEYPAD_4x4		0
#define keyIO_PORT					B
#define __IO_PORT__(PORT_NAME)		PORT##PORT_NAME
#define keyCHAR_PORT				__IO_PORT__(B)
#define keyCHAR_DDR					DDRB
#define keyCHAR_PIN					PINB




#define USE_LAB_OS_SERIAL			0
/* Baud rate used by the serial port tasks. */

#define USE_LAB_OS_PROTOCOL			0

#define USE_LAB_OS_TERMINAL			0

#define USE_LAB_OS_COMMAND			0

#define USE_LAB_OS_STEPPER			0

// ADC logger Application
#define USE_LAB_OS_ADC_LOG 			0
#define USE_LAB_OS_ADC	 			0



#endif /* LABOS_CONFIG_H */
