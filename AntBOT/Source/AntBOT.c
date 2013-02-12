/*
 * AntBOT.c
 *
 *  Created on: Jun 13, 2011
 *      Author: Andrey
 */

#include "AntBot.h"

// include bot modules
#include "BotControl.h"
#include "BotPower.h"
#include "BotLights.h"
#include "BotButton.h"
#include "BotServo.h"
#include "BotArm.h"
#include "BotWheelCtrl.h"
#include "BotAdc.h"
#include "lcd.h"
#include "mirf_driver.h"

void vStartAntBOT(void){

	PowerOn();
	DDRB = 0xFF;
	PORTB = 0xFF;

	///* initialize display, cursor off */
	lcd_init(LCD_DISP_ON);
	///* clear display and home cursor */
	lcd_clrscr();
	lcd_puts("Ant BOT>\nPower On");

	mirf_RX_ADDR_P0 = mirf_Default_ADDR;
	mirf_ShockB_init(2);

//	RC_SetUnits(500,7);
//	  test wheels
//	RC_SetUnits(500, 6);
//	RC_SetUnits(500, 5);
//	RC_SetUnits(100, 1);






#if(USE_BOT_CTRL == 1)
	vStartControlTask(mainCONTROL_PRIORITY);
#endif
#if(USE_BOT_LIGHTS == 1)
	vStartLightsTask( mainLIGHTS_PRIORITY );
#endif
#if(USE_BOT_BUTTON == 1)
	vStartButtonTask( mainBUTTON_PRIORITY, 10 );
#endif
#if(USE_BOT_ARM == 1)
	vStartArmTask(mainARM_PRIORITY);
#endif
#if(USE_BOT_WHEEL == 1)
	vStartWheelTask(mainWHEEL_PRIORITY);
#endif

#if(USE_BOT_SERVO == 1)
	RC_StartModule();
#endif

#if(USE_BOT_ADC == 1)
	vAdcInit(5);
#endif


}
