/*
 * core.h
 *
 *  Created on: Mar 27, 2011
 *      Author: Andrey
 */

#ifndef ADC_LOG_H_
#define ADC_LOG_H_
#include "LabOS.h"

#if(USE_LAB_OS_ADC_LOG == 1)

#include "task.h"

#ifndef mainADCLOG_PRIORITY
	#define mainADCLOG_PRIORITY				( tskIDLE_PRIORITY + 1 )
#endif

void vStartAdcLogTask( unsigned portBASE_TYPE cmdPriority);

#endif

#endif /* ADC_LOG_H_ */
