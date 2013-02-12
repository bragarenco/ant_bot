#include "display8x7seg.h"

#if(USE_LAB_OS_7_SEG_DISPLAY == 1)

static portTASK_FUNCTION( vDisplayTask, pvParameters );
void clearTab(char *tabRef);
char charTo7seg(char code);

char *tabRef;

char displayTab[DISPLAY_MEM_SIZE] = "---------";
unsigned char putCharPos = 0;


void DisplayInit();
void DisplayToIdleState();
void DisplayShowChar(char col_select, char ch);


void vStartDisplayTask(unsigned portBASE_TYPE displayPriority) {

	DisplayInit();

	/* The Tx task is spawned with a lower priority than the Rx task. */
	xTaskCreate( vDisplayTask, ( signed char * ) "Display", displaySTACK_SIZE, NULL, displayPriority, ( xTaskHandle * ) NULL );
}

static portTASK_FUNCTION( vDisplayTask, pvParameters ) {

	portTickType xLastExecutionTime;
	portTickType xTimeToWait = 4 / portTICK_RATE_MS;

	/* Just to stop compiler warnings. */
	(void) pvParameters;

	/* Initialize the variable used by the call to vTaskDelayUntil(). */
	xLastExecutionTime = xTaskGetTickCount();

	unsigned char col_select = 0;

	tabRef = (char*) &displayTab;

	DisplayClear();

	displayGoToX(0);

//		displayPrint("HELLO");
//		displayPrint(" 123 4567 890 ");


	for (;;) {

		// adjust clumn selector
		if (col_select > DISPLAY_SIZE-1)
			col_select = 0;

		// display off
		DisplayToIdleState();
		char ch = charTo7seg(tabRef[col_select]);

		DisplayShowChar(col_select, ch);

		// icrement column selector
		col_select++;

		/* This is a periodic task. Block until it is time to run again.
		 The task will execute every  xTimeToWait ms. */
		vTaskDelayUntil(&xLastExecutionTime, xTimeToWait);
//		taskYIELD();
	}

}

void DisplayCmd(char cmd, char ch) {
	// handle key
	if (cmd == 'l') {
		displayLeft(1);
	} else if (cmd == 'r') {
		DisplayRight(1);
	} else if (cmd == 'u') {
		displayLeft(8);
	} else if (cmd == 'd') {
		DisplayRight(8);
	} else if (cmd == '#') {
		DisplayClear();
	} else if (cmd == '*') {
		DisplayDeleteChar();
	} else {
		DisplayPutChar(cmd);
	}
}

void clearTab(char * tabRef) {

	for (unsigned char i = 0; i < DISPLAY_MEM_SIZE; i++) {
		tabRef[i] = 0;
	}

	//	return 0;
}

char charTo7seg(char code) {

	switch (code) {
	case '0':
		code = 0b0111111; // 0 zero
		break;
	case '1':
		code = 0b0000110; // 1
		break;
	case '2':
		code = 0b1011011; // 2
		break;
	case '3':
		code = 0b1001111; // 3
		break;
	case '4':
		code = 0b1100110; // 4
		break;
	case '5':
		code = 0b1101101; // 5
		break;
	case '6':
		code = 0b1111101; // 6
		break;
	case '7':
		code = 0b0000111; // 7
		break;
	case '8':
		code = 0b1111111; // 8
		break;
	case '9':
		code = 0b1101111; // 9
		break;
	case 'A':
		code = 0b1110111; // A
		break;
	case 'b':
		code = 0b1111100; // b
		break;
	case 'C':
		code = 0b0111001; // C
		break;
	case 'd':
		code = 0b1011110; // d
		break;
	case 'E':
		code = 0b1111001; // E
		break;
	case 'F':
		code = 0b1110001; // F
		break;
	case 'H':
		code = 0b1110110; // H
		break;
	case 'h':
		code = 0b1110100; // h
		break;
	case 'i':
		code = 0b0000010; // H
		break;
	case 'J':
		code = 0b0000111; // H
		break;
	case 'L':
		code = 0b0111000; // L
		break;
	case 'l':
		code = 0b0110000; // L
		break;
	case 'n':
		code = 0b1010100; // L
		break;
	case 'O':
		code = 0b0111111; // O
		break;
	case 'o':
		code = 0b1011100; // o
		break;
	case 'P':
		code = 0b1110011; // P
		break;
	case 'r':
		code = 0b1010000; // r
		break;
	case 'S':
		code = 0b1101101; // S
		break;
	case 't':
		code = 0b1111000; // t
		break;
	case 'U':
		code = 0b0111110; // t
		break;
	case 'u':
		code = 0b0011100; // t
		break;
	case '-':
		code = 0b1000000; // t
		break;
	case '*':
		code = 0b1110000; // *
		break;
	case '#':
		code = 0b1000011; // t
		break;

	default:
		code = 0b0000000; //  ' ' - WS

	}

	return code;
}

void DisplayClear() {
	clearTab(displayTab);
	displayGoToX(0);
	//  displayShowX(0);
	//  return putCharPos;

}

char DisplayDeleteChar() {
	if (putCharPos)
		displayTab[--putCharPos] = 0;

	return putCharPos;
}

void DisplayPutChar(char ch) {

	if (putCharPos < DISPLAY_MEM_SIZE)
		displayTab[putCharPos++] = ch;

	//  return putCharPos;
}

void displayPrint(char str[]) {

	unsigned char pos = 0;
	while (str[pos] != 0) {
		DisplayPutChar(str[pos++]);
	}

	//  return pos;
}

void displayGoToX(char pos) {
	putCharPos = pos;
}

void displayShowX(char pos) {
	tabRef = (char*) &displayTab + pos;
}

void displayLeft(unsigned char pos) {

	tabRef -= pos;
	if (tabRef < (char*) &displayTab)
		tabRef = (char*) &displayTab;

	//	return (unsigned char)(tabRef - (char*)&displayTab);
}

void DisplayRight(unsigned char pos) {
	tabRef += pos;
	if (tabRef > (char*) &displayTab + DISPLAY_MEM_SIZE - DISPLAY_SIZE)
		tabRef = (char*) &displayTab + DISPLAY_MEM_SIZE - DISPLAY_SIZE;

	//	return (unsigned char)(tabRef - (char*)&displayTab);
}
#endif

