/*
 * protocol.h
 *
 *  Created on: Jul 4, 2011
 *      Author: Andrey
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "LabOS.h"

#if(USE_LAB_OS_PROTOCOL == 1)
#include "serial.h"

#define PACK_LENGTH	26
#define STX	0x02
#define ETX	0x03
#define sendTime	0xFF //TIME SEND
#define IDpacket	0xAA //ID packet

void SendPack(char *pack, xComPortHandle pxPort);
void GetPack(char pack[PACK_LENGTH], xComPortHandle pxPort, portTickType xBlockTime );
#endif

#endif /* PROTOCOL_H_ */
