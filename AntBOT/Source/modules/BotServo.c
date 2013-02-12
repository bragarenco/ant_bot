/*
 * BotServo.c
 *
 *  Created on: Dec 5, 2012
 *      Author: Andrei
 */

#include "BotServo.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "task.h"


volatile int RC_Channels[RC_NR_OF] = {RC_RES/2,RC_RES/2,RC_RES/2,RC_RES/2,RC_RES/2,RC_RES/2,RC_RES/2,RC_RES/2};
volatile unsigned int RC_OCR_Values[RC_NR_OF+1] = {1,2,3,4,5,6,7,8,9};
volatile char RC_changed=1;
// contain 8 period in terms of OC counting and 1 idle period

static int RC_CurCnl = 8;

#define RC_SetIdleState() RC_CurCnl = 8
#define RC_IsIdleState() RC_CurCnl == 8


unsigned int _RC_T_DIV		= RC_T_DIV;
unsigned long _RC_F_CNT		= RC_F_CNT;
unsigned int _RC_F_RC		= RC_F;
unsigned int _RC_RC_PERIOD_IN_F_CNT_TICK = RC_PERIOD_IN_F_CNT_TICK;
unsigned long _RC_RC_MIN		= RC_MIN;
unsigned long _RC_RC_MAX		= RC_MAX;
unsigned int _RC_RC_RES		= RC_RES;
double		 _RC_RC_UNIT	= RC_UNIT;
double		 _RC_1_US_CNT	= RC_1_US_CNT;


void RC_IntInit();
void RC_PortInit();
void RC_Update();
void RC_OCR_Correction();


#define RC_SetAllPinDir() RC_DDR |= (		\
						RC0_EN << RC0_PIN | \
						RC1_EN << RC1_PIN | \
						RC2_EN << RC2_PIN | \
						RC3_EN << RC3_PIN | \
						RC4_EN << RC4_PIN | \
						RC5_EN << RC5_PIN | \
						RC6_EN << RC6_PIN | \
						RC7_EN << RC7_PIN )

#define RC_ClearAllPin() RC_PORT &= ~(		\
						RC0_EN << RC0_PIN | \
						RC1_EN << RC1_PIN | \
						RC2_EN << RC2_PIN | \
						RC3_EN << RC3_PIN | \
						RC4_EN << RC4_PIN | \
						RC5_EN << RC5_PIN | \
						RC6_EN << RC6_PIN | \
						RC7_EN << RC7_PIN )

#define RC_PinIsNotIdleState()	RC_PORT | (		\
						RC0_EN << RC0_PIN | \
						RC1_EN << RC1_PIN | \
						RC2_EN << RC2_PIN | \
						RC3_EN << RC3_PIN | \
						RC4_EN << RC4_PIN | \
						RC5_EN << RC5_PIN | \
						RC6_EN << RC6_PIN | \
						RC7_EN << RC7_PIN )

#if RC_T_DIV == 64
#define RC_TimerStart() TCCR3B |= (0<<CS32 | 1<<CS31 | 1<<CS30)
#elif RC_T_DIV == 8
#define RC_TimerStart() TCCR3B |= (0<<CS32 | 1<<CS31 | 0<<CS30)
#endif


#define RC_TimerStop() 	TCCR3B &= ~(1 << CS32 | 1 << CS31 | 1 << CS30)



void RC_StartModule() {
	RC_Update();
	RC_OCR_Correction();
	RC_SetIdleState();
	RC_PortInit();
	RC_IntInit();
	RC_TimerStop();
	RC_TimerStart();
}

void RC_PortInit() {
	RC_ClearAllPin();
	RC_SetAllPinDir();
}

void RC_IntInit() {

	ETIMSK |= 1 << OCIE3A;

	OCR3AH = RC_OCR_Values[8] >> 8;
	OCR3AL = RC_OCR_Values[8];
}






void RC_Update() {

	unsigned int RC_Sum = 0;

	for (int i = 0; i < 8; ++i) {
		int RC_Value = RC_Channels[i];
		if (RC_Value > RC_RES)
			RC_Value = RC_RES;
		if (RC_Value < 0)
			RC_Value = 0;


		RC_Channels[i] = RC_Value;

		RC_Sum += RC_Value;
	}

//	RC_Channels[8] = 9*RC_RES - RC_Sum;
}

void RC_OCR_Correction() {

	unsigned int RC_Sum = 0;

	for (int i = 0; i < 8; ++i) {
		int RC_Value = RC_Channels[i];
		int RC_OCR_Value = (float) RC_Value * RC_UNIT + RC_MIN;

		if (RC_OCR_Value > RC_MAX)
			RC_OCR_Value = RC_MAX;
		if (RC_OCR_Value < RC_MIN)
			RC_OCR_Value = RC_MIN;

		RC_OCR_Values[i] = RC_OCR_Value;

		RC_Sum += RC_OCR_Value;
	}

	RC_OCR_Values[8] = RC_PERIOD_IN_F_CNT_TICK - RC_Sum;
}


void RC_SetUnits(const int units, const int channel) {

	int RC_Value = units;
	if(channel<8){
		if (RC_Value > RC_RES)
			RC_Value = RC_RES;
		if (RC_Value < 0)
			RC_Value = 0;

		RC_Channels[channel] = RC_Value;
		RC_changed=1;
	}
}

int RC_GetUnits(const int channel) {

	int units = RC_Channels[channel];

	return units;
}

int RC_GetOCR(const int channel) {

	int units = RC_OCR_Values[channel];

	return units;
}

void RC_AddUnits(const int units, const int channel) {

	unsigned int RC_Value = RC_GetUnits(channel);

	RC_Value+=units;

	RC_SetUnits(RC_Value, channel);
}


typedef union {
	struct{
		unsigned char LOW;
		unsigned char HIGH;
	};

	unsigned int OCR;
}RC_OCR;

// signal period 20ms
// min pulse 0.9 ms
// max pulse 2.4 ms
SIGNAL(SIG_OUTPUT_COMPARE3A){
	register RC_OCR RC_OCRVal;
	//register unsigned int OCR_Value;

	RC_TimerStop();
	RC_ClearAllPin();

	if (RC_changed && RC_CurCnl ==8) {
		RC_OCR_Correction();
		RC_changed = 0;
	}

	if(RC_CurCnl>8){
		RC_CurCnl=0;
	}


	RC_OCRVal.LOW  = OCR3AL;
	RC_OCRVal.HIGH = OCR3AH;
	RC_OCRVal.OCR +=RC_OCR_Values[RC_CurCnl];
	OCR3AH = RC_OCRVal.HIGH;
	OCR3AL = RC_OCRVal.LOW;


	 switch(RC_CurCnl){
#if(RC0_EN==1)
	 case 0: RC0_PORT|= 1<< RC0_PIN; break;
#endif
#if(RC1_EN==1)
	 case 1: RC1_PORT|= 1<< RC1_PIN; break;
#endif
#if(RC2_EN==1)
	 case 2: RC2_PORT|= 1<< RC2_PIN; break;
#endif
#if(RC3_EN==1)
	 case 3: RC3_PORT|= 1<< RC3_PIN; break;
#endif
#if(RC4_EN==1)
	 case 4: RC4_PORT|= 1<< RC4_PIN; break;
#endif
#if(RC5_EN==1)
	 case 5: RC5_PORT|= 1<< RC5_PIN; break;
#endif
#if(RC6_EN==1)
	 case 6: RC6_PORT|= 1<< RC6_PIN; break;
#endif
#if(RC7_EN==1)
	 case 7: RC7_PORT|= 1<< RC7_PIN; break;
#endif
	 };

		RC_TimerStart();
		RC_CurCnl++;
//		if(RC_CurCnl>8) RC_CurCnl=0;

}
