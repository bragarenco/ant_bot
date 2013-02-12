/*
 * mirf_driver.h
 *
 *  Created on: 06.02.2013
 *      Author: Alexandru
 */

#ifndef MIRF_DRIVER_H_
#define MIRF_DRIVER_H_
#include <inttypes.h>

//#include "mirf.h"
#include "nrf24l01.h"

#define	mirf_MAX_Nr_commands	32		// < 255
#define mirf_Address_width		4
#define mirf_MaxPayload			32
#define mirf_Default_ADDR		0xE7E7E7E7

void	mirf_ShockB_init(char chanel);
uint32_t mirf_RX_ADDR_P0;				// deafault receive address
uint32_t mirf_RXpack_addr;				// address captured from RXPack
uint8_t mirf_RXpack_len;				// length of packed without 4B(RXpack_addr)

char mirf_RXpack_buff[28];

void	mirf_addcommand(uint8_t command_ID, int *ptr_mirf_func);
void	mirf_loop();
void	mirf_timer_loop(uint8_t timer_ms);

#endif /* MIRF_DRIVER_H_ */
