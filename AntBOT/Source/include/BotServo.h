/*
 * BotServo.h
 *
 *  Created on: Dec 5, 2012
 *      Author: Andrei
 */

#ifndef BOT_SERVO_H_
#define BOT_SERVO_H_
#include "AntBOT.h"

#ifndef RC_PORT
#define RC_PORT PORTD
#endif

#ifndef RC_DDR
#define RC_DDR DDRD
#endif


#ifndef RC0_DDR
#define RC0_DDR RC_DDR
#endif
#ifndef RC1_DDR
#define RC1_DDR RC_DDR
#endif
#ifndef RC2_DDR
#define RC2_DDR RC_DDR
#endif
#ifndef RC3_DDR
#define RC3_DDR RC_DDR
#endif
#ifndef RC4_DDR
#define RC4_DDR RC_DDR
#endif
#ifndef RC5_DDR
#define RC5_DDR RC_DDR
#endif
#ifndef RC6_DDR
#define RC6_DDR RC_DDR
#endif
#ifndef RC7_DDR
#define RC7_DDR RC_DDR
#endif


#ifndef RC0_PORT
#define RC0_PORT RC_PORT
#endif
#ifndef RC1_PORT
#define RC1_PORT RC_PORT
#endif
#ifndef RC2_PORT
#define RC2_PORT RC_PORT
#endif
#ifndef RC3_PORT
#define RC3_PORT RC_PORT
#endif
#ifndef RC4_PORT
#define RC4_PORT RC_PORT
#endif
#ifndef RC5_PORT
#define RC5_PORT RC_PORT
#endif
#ifndef RC6_PORT
#define RC6_PORT RC_PORT
#endif
#ifndef RC7_PORT
#define RC7_PORT RC_PORT
#endif

#ifndef RC0_PIN
#define RC0_PIN 0
#endif
#ifndef RC1_PIN
#define RC1_PIN 1
#endif
#ifndef RC2_PIN
#define RC2_PIN 2
#endif
#ifndef RC3_PIN
#define RC3_PIN 3
#endif
#ifndef RC4_PIN
#define RC4_PIN 4
#endif
#ifndef RC5_PIN
#define RC5_PIN 5
#endif
#ifndef RC6_PIN
#define RC6_PIN 6
#endif
#ifndef RC7_PIN
#define RC7_PIN 7
#endif

#ifndef RC0_EN
#define RC0_EN 0
#endif
#ifndef RC1_EN
#define RC1_EN 0
#endif
#ifndef RC2_EN
#define RC2_EN 0
#endif
#ifndef RC3_EN
#define RC3_EN 0
#endif
#ifndef RC4_EN
#define RC4_EN 0
#endif
#ifndef RC5_EN
#define RC5_EN 0
#endif
#ifndef RC6_EN
#define RC6_EN 0
#endif
#ifndef RC7_EN
#define RC7_EN 0
#endif

#define RC_F_CPU 		8000000
#define RC_T_DIV 		8
#define RC_F_CNT		RC_F_CPU/RC_T_DIV
// 4M/64 = 62500
// 4M/8  = 500000


#define RC_TCNT_MAX	0xFFFF

#define RC_F        50
#define RC_PERIOD_IN_F_CNT_TICK RC_F_CNT/RC_F
// 62500/50 = 1250
// 500000/50 = 10000
#if(RC_PERIOD_IN_F_CNT_TICK > RC_TCNT_MAX)
#error "BAD configuration for RC module: RC signal Period in TCNT tick > TCNT_MAX"
#endif

#define RC_PERIOD_IN_US 20000
#define RC_1_US_CNT 	1.0*RC_F_CNT/1000000
#define RC_MIN_US		1000 // 900
#define RC_MAX_US		2000 //2400

#define RC_MIN		RC_MIN_US * (RC_1_US_CNT)
#define RC_MAX		RC_MAX_US * (RC_1_US_CNT)
#define RC_PERIOD_IN_F_CNT_TICK  RC_PERIOD_IN_US *(RC_1_US_CNT)

#define RC_RES		1000
#define RC_UNIT		1.0*(RC_MAX-RC_MIN)/RC_RES

#define RC_NR_OF	8


void RC_StartModule();
void RC_SetUnits(const int units,const int channel);
int RC_GetUnits(const int channel);
void RC_AddUnits(const int units, const int channel);



#endif /* BOTSERVO_H_ */
