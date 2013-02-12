// transmitter

#include "protocol.h"

#if(USE_LAB_OS_PROTOCOL == 1)

char GetControlSumm(char pack[]) {
	char controlSum = 0;
	for (int i = 0; i < PACK_LENGTH - 2; i++)
		controlSum += pack[i];
	return controlSum;
}

char TestForPack(char pack[]) {
	if (pack[0] != STX)
		return pdFALSE;
	if (pack[PACK_LENGTH - 1] != ETX)
		return pdFALSE;
	if (pack[PACK_LENGTH - 2] != GetControlSumm(pack))
		return pdFALSE;
	return pdTRUE;
}


char PackNr = 0;

void PackData(char pack[]) {
	pack[0] = STX;
	pack[1] = PackNr++;
	pack[2] = sendTime; //SEND TIME
	pack[PACK_LENGTH-2] = GetControlSumm(pack);
	pack[PACK_LENGTH-1] = ETX;
}

void SendPack(char pack[], xComPortHandle pxPort) {

	// packing data
	PackData(txPack);

	for (int i = 0; i < PACK_LENGTH; i++)
		xSerialPutChar(pxPort, pack[i], 0);
}


void GetPack(char pack[], xComPortHandle pxPort,	portTickType xBlockTime) {

	// clear pack
	for (int i = 0; i < PACK_LENGTH; ++i) {
		pack[i] = 0;
	}

	do {
		char rxChar;
		// get a char
		while (xSerialGetChar(pxPort, &rxChar, xBlockTime) == pdFALSE)
			;
		// push to pack
		for (int i = 0; i < PACK_LENGTH-1; ++i) {
			pack[i] = pack[i+1];
		}
		pack[PACK_LENGTH-1]=rxchar;

	} while (!TestForPack(pack));


//	char rxchar;
//	char j = 0;
//	while (xSerialGetChar(pxPort, &rxchar, xBlockTime)) {
//		pack[j] = rxchar;
//		j++;
//		if (rxchar == 0x03)
//			break;
//	}

}

#endif

