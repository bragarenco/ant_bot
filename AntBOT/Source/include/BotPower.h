/*
 * BotPower.h
 *
 *  Created on: Dec 21, 2012
 *      Author: Andrei
 */

#ifndef BOT_POWER_H_
#define BOT_POWER_H_
#include <avr/io.h>
#include "AntBOT.h"

#define POWER_ON_PORT 			PORTA
#define POWER_ON_DDR 			DDRA
#define	POWER_ON_LINE			PA3


void MaintainPowerOn(void);		// pentru ca robotul sa-si mentina alimentarea pornita
void Shutdown(void);			// pentru a deconecta alimentarea complet


void PowerOn();
void PowerOff();


#endif /* BOT_POWER_H_ */
