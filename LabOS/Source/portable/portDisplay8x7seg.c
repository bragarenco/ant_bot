/*
 * portDisplay8x7seg.c
 *
 *  Created on: Apr 24, 2011
 *      Author: Andrey
 */
#include "LabOS.h"

#if(USE_LAB_OS_7_SEG_DISPLAY == 1)

void DisplayInit(){
	displaySELECT_DDR = 0xFF;
	displayCHAR_DDR = 0xFF;
	displayCHAR_PORT = 0x00;
}
void DisplayToIdleState(){
	displaySELECT_PORT = 0xFF;

}
void DisplayShowChar(char col_select, char ch){
	// show the char
	displayCHAR_PORT = ch;
	// enable the column
	displaySELECT_PORT = ~(1 << col_select);
}
#endif
