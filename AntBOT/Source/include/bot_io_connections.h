#ifndef _BOT_IO_CONNECTIONS_
#define _BOT_IO_CONNECTIONS_

#include<avr/io.h>

#define POWER_ON_PORT 			PORTA
#define POWER_ON_DDR 			DDRA
#define	POWER_ON_LINE			PA3

#define	MOTOR_CONTROL_PORT		PORTB
#define	MOTOR_CONTROL_DDR		DDRB
#define	MOTOR_CONTROL_PIN		PINB
#define	MOTOR_FEEDBACK_PORT		PORTF
#define MOTOR_FEEDBACK_DDR		DDRF
#define MOTOR_FEEDBACK_PIN		PINF
#define L_MOTOR_CNTRL			PB5	// TREBUIE VERIFICAT
#define R_MOTOR_CNTRL			PB6
#define	C_MOTOR_CNTRL			PB7
#define	L_MOTOR_FB				PF0
#define	R_MOTOR_FB				PF7
#define	L_MOTOR_ADC_FB			0		//MASCA PENTUR ADMUX
#define	R_MOTOR_ADC_FB			7		//MASCA PENTUR ADMUX


#define BUTTON_PORT				PORTD
#define	BUTTON_DDR				DDRD
#define	BUTTON_PIN				PIND
#define	BUTTON1					PIND4
#define	BUTTON2					PIND5
#define	BUTTON3					PIND6
#define	BUTTON4					PIND7

#define	LCD_PORT				PORTC
#define	LCD_DDR					DDRC
#define	LCD_PIN					PINC
#define	LCD_RS					PC1
#define	LCD_RW					PC2
#define	LCD_E					PC3
#define	LCD_D4					PC4
#define	LCD_D5					PC5
#define	LCD_D6					PC6
#define	LCD_D7					PC7

#define	BUMPER_REF_PORT			PORTB	
#define	BUMPER_REF_DDR			DDRB
#define	BUMPER_REF_PIN			PINB
#define	BUMPER_REF 				PB4
#define	BUMPER_REF_OCR			OCR0

#define	WALL_SENSOR_EN_PORT		PORTG
#define	WALL_SENSOR_EN_PIN		PING
#define	WALL_SENSOR_EN_DDR		DDRG
#define	EDGE_SENSOR_EN_PORT		PORTG
#define	EDGE_SENSOR_EN_PIN		PING
#define	EDGE_SENSOR_EN_DDR		DDRG

#define	B_WALL_SENSOR_EN		PG0	
#define	F_WALL_SENSOR_EN		PG1
#define	EDGE_SENSOR_EN 			PG2

#define	LINE_SENSOR_EN_PORT		PORTA
#define	LINE_SENSOR_EN_PIN		PINA
#define	LINE_SENSOR_EN_DDR		DDRA
#define	LINE_SENSOR_EN 			PA2

#define	EDGE_SENSOR_IN_PORT		PORTA
#define	EDGE_SENSOR_IN_DDR		DDRA
#define	EDGE_SENSOR_IN_PIN		PINA
#define	FR_EDGE_SENSOR_IN		PINA0
#define	FL_EDGE_SENSOR_IN		PINA1
#define	BL_EDGE_SENSOR_IN		PINA5
#define	BR_EDGE_SENSOR_IN		PINA6

#define	B_WALL_SENSOR_IN_PORT	PORTA
#define	B_WALL_SENSOR_IN_DDR	DDRA
#define	B_WALL_SENSOR_IN_PIN	PINA
#define	BL_WALL_SENSOR_IN		PINA4
#define	BR_WALL_SENSOR_IN		PINA7

#define	F_WALL_SENSOR_IN_PORT	PORTF
#define	F_WALL_SENSOR_IN_DDR	DDRF
#define	F_WALL_SENSOR_IN_PIN	PINF
#define	FL_WALL_SENSOR_IN		PINF5
#define	FC_WALL_SENSOR_IN		PINF4
#define	FR_WALL_SENSOR_IN		PINF1
#define	FL_WALL_SENSOR_ADC_IN	5			//MASCA PENTUR ADMUX
#define	FC_WALL_SENSOR_ADC_IN	4			//MASCA PENTUR ADMUX
#define	FR_WALL_SENSOR_ADC_IN	1			//MASCA PENTUR ADMUX

#define	LINE_SENSOR_IN_PORT		PORTF
#define	LINE_SENSOR_IN_DDR		DDRF
#define	LINE_SENSOR_IN_PIN		PINF
#define	L_LINE_SENSOR_IN		PINF6
#define	C_LINE_SENSOR_IN		PINF3
#define	R_LINE_SENSOR_IN		PINF2
#define	L_LINE_SENSOR_ADC_IN	6			//MASCA PENTUR ADMUX
#define	C_LINE_SENSOR_ADC_IN	3			//MASCA PENTUR ADMUX
#define	R_LINE_SENSOR_ADC_IN	2			//MASCA PENTUR ADMUX
							
#define	RF_PORT 				PORTB
#define	RF_PIN 					PINB
#define	RF_DDR 					DDRB
#define	RF_PORT1 				PORTE
#define	RF_PIN1					PINE
#define	RF_DDR1					DDRE
#define	RF_SS					PE6
#define	RF_CE					PE7
#define	RF_IRQ  				PB0
#define	RF_SCK					PB1
#define	RF_MOSI					PB2
#define	RF_MISO					PB3

//#define
//#define
	


#endif
