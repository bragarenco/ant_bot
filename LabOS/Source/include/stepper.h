

#ifndef STEPPER_H
#define STEPPER_H

#include "LabOS.h"

#if(USE_LAB_OS_STEPPER == 1)
#include "task.h"

#ifndef mainSTEPPER_PRIORITY
#define mainSTEPPER_PRIORITY	( tskIDLE_PRIORITY + 1 )
#endif
#ifndef stepperSTACK_SIZE
#define stepperSTACK_SIZE	configMINIMAL_STACK_SIZE
#endif

void vStartStepperTask( unsigned portBASE_TYPE displayPriority);

void StepsFWD(int steps);
void StepsREW(int steps);
void SteperStop();
void SteperFullStep();
void SteperHalfStep();

#endif
#endif
