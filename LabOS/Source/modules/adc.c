/*
    FreeRTOS V6.1.0 - Copyright (C) 2010 Real Time Engineers Ltd.

    ***************************************************************************
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

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/*
Changes from V1.2.3

	+ The function xPortInitMinimal() has been renamed to 
	  xSerialPortInitMinimal() and the function xPortInit() has been renamed
	  to xSerialPortInit().

Changes from V2.0.0

	+ Delay periods are now specified using variables and constants of
	  portTickType rather than unsigned long.
	+ xQueueReceiveFromISR() used in place of xQueueReceive() within the ISR.

Changes from V2.6.0

	+ Replaced the inb() and outb() functions with direct memory
	  access.  This allows the port to be built with the 20050414 build of
	  WinAVR.
*/

/* BASIC INTERRUPT DRIVEN SERIAL PORT DRIVER. */


#include "adc.h"


#if(USE_LAB_OS_ADC == 1)


#define NR_OF_ADC_CHANALS 4
#define ADD_RES 2
char x[10]="HERE!!";
int adcTab[NR_OF_ADC_CHANALS];
int adcTabTmp[NR_OF_ADC_CHANALS];
char x1[10]="HERE_END";
int adcData;
int adcChanel = 0;
char adcChanelCnt = 0;

/* Constants for writing to ADCSRA. */
#define adc_ENABLE				( 1<<ADEN )
#define adc_START_CONVERSION	( 1<<ADSC )

#define adc_INT_ENABLE			( 1<<ADIE )

///* ADCSRA */
//#define ADEN    7
//#define ADSC    6
//#define ADATE   5
//#define ADIF    4
//#define ADIE    3
//#define ADPS2   2
//#define ADPS1   1
//#define ADPS0   0
//
///* ADMUX */
//#define REFS1   7
//#define REFS0   6
//#define ADLAR   5
//#define MUX4    4
//#define MUX3    3
//#define MUX2    2
//#define MUX1    1
//#define MUX0    0

#define serBAUD_DIV_CONSTANT			( ( unsigned long ) 16 )


int GetAdcData(char chanel){
	int result;

	if(chanel > NR_OF_ADC_CHANALS-1)
		result = -1;
	else
		result = adcTab[chanel];

	return result;

}

void GetAdcVoltage(float* voltage){
 	*voltage  = ((float)5 /1024);
 	*voltage *= adcData;
}


#define vAdcInterruptOn()									\
{															\
	unsigned char ucByte;									\
															\
	ucByte = ADCSRA;										\
	ucByte |= adc_INT_ENABLE;								\
	ADCSRA = ucByte;										\
}																				
/*-----------------------------------------------------------*/

#define vAdcInterruptOff()									\
{															\
	unsigned char ucByte;									\
															\
	ucByte = ADCSRA;											\
	ucByte &= ~adc_INT_ENABLE;								\
	ADCSRA = ucByte;											\
}
/*-----------------------------------------------------------*/
#define vAdcEnable()										\
{															\
	unsigned char ucByte;									\
															\
	ucByte = ADCSRA;										\
	ucByte |= adc_ENABLE;									\
	ADCSRA = ucByte;										\
}
/*-----------------------------------------------------------*/

#define vAdcDisable()										\
{															\
	unsigned char ucByte;									\
															\
	ucByte = ADCSRA;										\
	ucByte &= ~adc_ENABLE;									\
	ADCSRA = ucByte;										\
}
/*-----------------------------------------------------------*/

#define vAdcStartConversion()								\
{															\
	unsigned char ucByte;									\
															\
	ucByte = ADCSRA;										\
	ucByte |= adc_START_CONVERSION;						\
	ADCSRA = ucByte;										\
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

#define vAdcSetPrescaler(value)								\
{															\
	unsigned char ucByte;									\
															\
	ucByte = ADCSRA;										\
	ucByte &= ~0x07;						\
	ucByte |= value;										\
	ADCSRA = ucByte;										\
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

#define vAdcSetAdMux(value)									\
{															\
	unsigned char ucByte;									\
															\
	ucByte = ADMUX;										\
	ucByte &= ~0x1F;										\
	ucByte |= value;										\
	ADMUX = ucByte;										\
}
/*-----------------------------------------------------------*/


void vAdcInit( char cPrescaler )
{
	portENTER_CRITICAL();
	{
		vAdcEnable();
		vAdcSetPrescaler(cPrescaler);
		vAdcSetAdMux(0);
		vAdcInterruptOn();
		vAdcStartConversion();
//		PORTA=ADCSRA;


	}
	portEXIT_CRITICAL();
}

/*-----------------------------------------------------------*/

//signed portBASE_TYPE xAdcGetData( xComPortHandle pxPort, signed char *pcRxedChar, portTickType xBlockTime )
//{
//	/* Only one port is supported. */
//	( void ) pxPort;
//
//	/* Get the next character from the buffer.  Return false if no characters
//	are available, or arrive before xBlockTime expires. */
//	if( xQueueReceive( xRxedChars, pcRxedChar, xBlockTime ) )
//	{
//		return pdTRUE;
//	}
//	else
//	{
//		return pdFALSE;
//	}
//}
/*-----------------------------------------------------------*/

void vAdcOff( )
{

	/* The parameter is not used. */
//	( void ) xPort;

	/* Turn off the interrupts.  We may also want to delete the queues and/or
	re-install the original ISR. */

	portENTER_CRITICAL();
	{
		vAdcInterruptOff();
		vAdcDisable();
	}
	portEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

ISR( ADC_vect )
{

	adcData  =		ADCL;
	adcData |= (int)ADCH << 8;


	if(++adcChanelCnt>(NR_OF_ADC_CHANALS<<ADD_RES)-1){
		adcChanelCnt = 0;
		for(int i = 0; i < NR_OF_ADC_CHANALS; i++){
			adcTab[i] = adcTabTmp[i];
			adcTabTmp[i] = 0;
		}
	}

	adcChanel = adcChanelCnt>>ADD_RES;

	adcTabTmp[adcChanel] += adcData;



	vAdcSetAdMux(adcChanel);

//	PORTA++;

	vAdcStartConversion();

	return;
}
/*-----------------------------------------------------------*/
#endif

