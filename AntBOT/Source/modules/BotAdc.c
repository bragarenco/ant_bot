/*
 * BotAdc.c
 *
 *  Created on: Dec 27, 2012
 *      Author: Andrei
 */

#include "BotAdc.h"


#if(USE_BOT_ADC == 1)
#include <avr/interrupt.h>
#include <avr/io.h>

#define ADC_REF_EXT		0
#define ADC_REF_AVCC	1
#define ADC_REF_RSVD	2
#define ADC_REF_INT		3



#define NR_OF_ADC_CHANALS 8
char x[]="ADC_DATA";
int adcTab[NR_OF_ADC_CHANALS];
char x1[]="ADC_END";
int adcData;
int adcChanel = 0;



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


int GetAdcData(const unsigned char chanel){
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
	ucByte |= adc_START_CONVERSION;							\
	ADCSRA = ucByte;										\
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

#define vAdcSetPrescaler(value)								\
{															\
	unsigned char ucByte;									\
															\
	ucByte = ADCSRA;										\
	ucByte &= ~0x07;										\
	ucByte |= value;										\
	ADCSRA = ucByte;										\
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

#define vAdcSetAdMux(value)									\
{															\
	unsigned char ucByte;									\
															\
	ucByte = ADMUX;											\
	ucByte &= ~(1<<MUX0|1<<MUX1|1<<MUX2|1<<MUX3|1<<MUX4);	\
	ucByte |= value;										\
	ADMUX = ucByte;											\
}
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/

#define vAdcSetAdRef(value)									\
{															\
	unsigned char ucByte;									\
															\
	ucByte = ADMUX;											\
	ucByte &= ~(1<<REFS0|1<<REFS1);							\
	ucByte |= value<<REFS0;									\
	ADMUX = ucByte;											\
}
/*-----------------------------------------------------------*/


void vAdcInit( char cPrescaler )
{
	portENTER_CRITICAL();
	{
		vAdcEnable();
		vAdcSetPrescaler(cPrescaler);
		vAdcSetAdRef(ADC_REF_AVCC);
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

	adcTab[adcChanel++] = adcData;

	if(adcChanel>7)adcChanel=0;

	vAdcSetAdMux(adcChanel);


	vAdcStartConversion();

	return;
}
/*-----------------------------------------------------------*/
#endif

