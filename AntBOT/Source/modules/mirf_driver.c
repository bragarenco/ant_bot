/*
 * mirf_driver.c
 *
 *  Created on: 06.02.2013
 *      Author: Alexandru
 */

#include "mirf_driver.h"
#include <util/delay.h>		// MCU Specific
//#include "nRF24L01.h"

void	mirf_ShockB_init(char chanel){
	// ports and spi init
	spi_init();
	IRQ_DDR();
	_CE_DDR |= (1<<_CE_PIN);
	_CSN_DDR |= (1<<_CSN_PIN);
	IRQ_DDR();

//    mirf_CE_lo;
//    mirf_CSN_hi;

	// Disable Enhanced ShockBurst

	NRF24L01_Set_ShockBurst(_ShockBurst_ON);

	// RF output power in TX mode = 0dBm (Max.)
	// Set LNA gain
	NRF24L01_WriteReg(W_REGISTER | RF_SETUP, 0x07 | _1Mbps);

	NRF24L01_Set_Address_Width(mirf_Address_width);

	uint8_t vars[4], *ptr;
	ptr = &mirf_RX_ADDR_P0;
	vars[0] = *ptr++;
	vars[1] = *ptr++;
	vars[2] = *ptr++;
	vars[3] = *ptr;

	NRF24L01_Set_RX_Pipe(0,vars, mirf_Address_width,mirf_MaxPayload);

	NRF24L01_Set_CH(chanel);

	NRF24L01_Set_TX_Address(vars, mirf_Address_width); // Set Transmit address

	// Bits 4..6: Reflect interrupts as active low on the IRQ pin
	// Bit 3: Enable CRC
	// Bit 2: CRC 1 Byte
	// Bit 1: Power Up
	NRF24L01_WriteReg(W_REGISTER | CONFIG, 0x0A | _RX_MODE);

	NRF24L01_WriteReg(W_REGISTER | FEATURE, 0x04);
	NRF24L01_WriteReg(W_REGISTER | DYNPD, 0x3F);
	NRF24L01_WriteReg(ACTIVATE, 0x7F);				// activate command for DYNPD

	_delay_us(1500);



//	mirf_config_register(FEATURE, 0x04);	// bit 2 set for dynamic payload
//	mirf_config_register(DYNPD, 0x3F);		// enable dynamic for all pipes

}

void mirf_addcommand(uint8_t command_ID, int *ptr_mirf_func){

}

void	mirf_loop(){

}

void	mirf_timer_loop(uint8_t timer_ms){

}
