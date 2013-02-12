/*
 * portKeypad3x4.c
 *
 *  Created on: Apr 24, 2011
 *      Author: Andrey
 */
#include "LabOS.h"

#if(USE_LAB_OS_KEYPAD_4x4 == 1)

//init the keypad port direction output for columns and input for rows
void KeyInit(){
	keyCHAR_DDR = 0x0F;
}

// set the keypad in idle state all columns driven by "0"
void KeyToIdleState(){
	keyCHAR_PORT = 0xf0;
}

// detect if any row was activated by "0"
char KeyPressed(){
	return ((~keyCHAR_PIN & 0xF0)>0);
}

//select a column
void KeyActivateColumn(char col_select){
	keyCHAR_PORT = 0xFF & ~(1 << col_select);
	keyCHAR_PORT;
}
// capture the port state as key code
char KeyGet(){
	return keyCHAR_PIN;
}

#endif
