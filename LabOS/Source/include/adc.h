
#ifndef ADC_H
#define ADC_H

#include "LabOS.h"

#if(USE_LAB_OS_ADC == 1)
#include <avr/interrupt.h>
#include <avr/io.h>
#include "task.h"

int GetAdcData(char chanel);
void GetAdcVoltage(float* voltage);
void vAdcInit( char cPrescaler );

#endif
#endif
