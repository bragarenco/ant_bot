/*
    FreeRTOS V6.1.0 - Copyright (C) 2010 Real Time Engineers Ltd.

    *******  ********************************************************************
    *                                                                         *
    * If you are:                                                             *
    *                                                                         *
    *    + New to FreeRTOS,                                                   *
    *    + Wanting to learn FreeRTOS or multitasking in general quickly       *
    *    + Looking for basic training,                                        *
    *    + Wanting to improve your FreeRTOS skills and productivity           *
    *                                                                         *
    * then take a look at the FreeRTOS books - available as PDF or paperback  *
    *                                                                         *
    *        "Using the FreeRTOS Real Time Kernel - a Practical Guide"        *
    *                  http://www.FreeRTOS.org/Documentation                  *
    *                                                                         *
    * A pdf reference manual is also available.  Both are usually delivered   *
    * to your inbox within 20 minutes to two hours when purchased between 8am *
    * and 8pm GMT (although please allow up to 24 hours in case of            *
    * exceptional circumstances).  Thank you for your support!                *
    *                                                                         *
    ***************************************************************************
*/

#ifndef ANTBOT_CONFIG_H
#define ANTBOT_CONFIG_H


/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

#define USE_BOT_CTRL			0

// BOT Lights pin configuration
#define USE_BOT_LIGHTS			0
#define LIGHTS_DDR  			DDRE
#define LIGHTS_PORT 			PORTE
#define PIN_RF					PIN2
#define PIN_RB					PIN3
#define PIN_LB					PIN4
#define PIN_LF					PIN5

// BOT Button pin configuration
#define USE_BOT_BUTTON			0
#define BUTTON_PORT				PORTD
#define	BUTTON_DDR				DDRD
#define	BUTTON_PIN				PIND
#define	PIN_BUTTON_1			PIN4
#define	PIN_BUTTON_2			PIN5
#define	PIN_BUTTON_3			PIN6
#define	PIN_BUTTON_4			PIN7


// BOT Arm pin configuration
#define USE_BOT_ARM		0
#define	ARM_PORT		PORTB
#define	ARM_DDR			DDRB
#define	ARM_PIN			PIN7

#define USE_BOT_ADC		1
#define ADC0_EN			1
#define ADC1_EN			1
#define ADC2_EN			1
#define ADC3_EN			1
#define ADC4_EN			1
#define ADC5_EN			1
#define ADC6_EN			1
#define ADC7_EN			1



// BOT Arm RC Channel configuration
#define USE_BOT_SERVO	1
#define RC_PORT			ARM_PORT
#define RC_DDR			ARM_DDR
#define RC7_EN 			0
#define RC7_PORT		ARM_PORT
#define RC7_DDR			ARM_DDR
#define RC7_PIN			ARM_PIN

// BOT Wheels Config
#define USE_BOT_WHEEL	1
#define	WHEELS_PORT		PORTB
#define	WHEELS_DDR		DDRB
#define	WR_PIN			PIN5
#define	WL_PIN			PIN6
#define WR_ADC			0
#define WL_ADC			7
// BOT Wheels RC Channel configuration

#define RC5_EN 			1
#define RC5_PORT		WHEELS_PORT
#define RC5_DDR			WHEELS_DDR
#define RC5_PIN			WR_PIN
#define RC6_EN 			0
#define RC6_PORT		WHEELS_PORT
#define RC6_DDR			WHEELS_DDR
#define RC6_PIN			WL_PIN


#endif /* LABOS_CONFIG_H */
