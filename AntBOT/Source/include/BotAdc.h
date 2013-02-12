/*
 * BotAdc.h
 *
 *  Created on: Dec 21, 2012
 *      Author: Andrei
 */

#ifndef BOT_ADC_H_
#define BOT_ADC_H_


#include "AntBOT.h"

#if(USE_BOT_ADC == 1)



int GetAdcData(const unsigned char chanel);
void GetAdcVoltage(float* voltage);
void vAdcInit( char cPrescaler );

#endif


#endif /* BOTADC_H_ */
