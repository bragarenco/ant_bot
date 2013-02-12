#include "stepper.h"

#if(USE_LAB_OS_STEPPER == 1)

static portTASK_FUNCTION( vStepperTask, pvParameters );

int stepNr = 0;
int stepEnd = 0;

struct flagstruct{
 char freeRun:1;
 char runFWD:1;
 char runFullStep:1;
 char pause:1;// suspend

}stepperFlag;


void SetStep(unsigned char stepNr);



void vStartStepperTask( unsigned portBASE_TYPE displayPriority){

	DDRD  |= 0xF0;
	PORTD |= 0xF0;

	stepperFlag.freeRun = 0;
	stepperFlag.runFWD = 1;
	stepperFlag.runFullStep = 1;

	/* The Tx task is spawned with a lower priority than the Rx task. */
	xTaskCreate( vStepperTask, ( signed char * ) "Stepper", stepperSTACK_SIZE, NULL, displayPriority, ( xTaskHandle * ) NULL );


}


static portTASK_FUNCTION( vStepperTask, pvParameters )
{
portTickType xTimeToWait = 100;

//char stepStrVal[6];
	/* Just to stop compiler warnings. */
	( void ) pvParameters;

	SetStep(stepNr);
	
	//StepsFWD(2000);

	for( ;; )
	{
	   	vTaskDelay( xTimeToWait );

		if(stepperFlag.pause)
			continue;

		if(stepNr < stepEnd){
			SetStep(++stepNr);
			if(stepperFlag.freeRun)
				stepEnd++;
		}else if(stepNr > stepEnd){
			SetStep(--stepNr);
			if(stepperFlag.freeRun)
				stepEnd--;
		}else{
			// adjust on stop to prevent overflow
			//unsigned char realStep = stepNr & 0x07;
			//stepNr = stepEnd = realStep;
		}

//		intToStr(stepNr, stepStrVal);
//		displayClear();
//		displayPrint("StEP ");
//		displayPrint(stepStrVal);

	}
}


char stepperTab[8] = {0b0001,
					  0b0011,
					  0b0010,
					  0b0110,
					  0b0100,
					  0b1100,
					  0b1000,
					  0b1001};
char str[6];
void SetStep(unsigned char realStepNr){
	char stepStrVal[6];

	realStepNr &= 0x07;

	if (stepperFlag.runFullStep){
		realStepNr&=~0x01;
	}

	unsigned char stepPin = stepperTab[realStepNr] << 4;

	PORTD &= 0x0F;
	PORTD |= ~stepPin & 0xF0;
}

inline void StepsFWD(int steps){
	stepEnd+=steps;
}
inline void StepsREW(int steps){
	stepEnd-=steps;
}
inline void SteperStop(){
	stepEnd=stepNr;
}
void SteperFullStep(){
	stepperFlag.runFullStep = 1;
}
void SteperHalfStep(){
	stepperFlag.runFullStep = 0;

}


//
//char StepperCommand(char ch){
//		// send char to display
//		displayPushCh(ch);
//
//		// handle key
//		if(ch == '1'){
//			// forward 1
//			StepsFWD(1);
//		}else
//		if(ch == '2'){
//			// forward 10
//			StepsFWD(10);
//		}else
//		if(ch == '3'){
//			// forward 100
//			StepsFWD(100);
//		}else
//		if(ch == '4'){
//			// backward 1
//			StepsREW(1);
//		}else
//		if(ch == '5'){
//			// backward 10
//			StepsREW(10);
//		}else
//		if(ch == '6'){
//			// backward 100
//			StepsREW(100);
//		}else
//		if(ch == '7'){
//			// full step
//			SteperFullStep();
//		}else
//		if(ch == '8'){
//			// halfstep
//			SteperHalfStep();
//		}else
//		if(ch == '0'){
//			// stop
//			SteperStop();
//		}
//	return 1;
//}


#endif
