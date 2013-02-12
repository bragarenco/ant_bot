/*
 * mirf.h
 *
 *  Created on: 06.02.2013
 *      Author: Alexandru
 */

#ifndef _MIRF_H_
#define _MIRF_H_
#include <avr/io.h>
typedef unsigned char uint8_t;
// Mirf settings
#define mirf_CH         2		// frequency channel
#define mirf_PAYLOAD    32
#define	mirf_ADDR_len	4		// 2 , 3 or 4
#define mirf_CONFIG     ( (1<<MASK_RX_DR) | (1<<EN_CRC) | (0<<CRCO) )

// Pin definitions for chip select and chip enabled of the MiRF module
#define CE  PE7
#define CSN PB0
#define IRQ (!(PINE & (1<<PE6)))

#define CSN_PORT	PORTB
#define CE_PORT		PORTE
#define CSN_DDR		DDRB
#define CE_DDR		DDRE
#define IRQ_DDR()	(DDRE &= ~(1<<PE6))


// Definitions for selecting and enabling MiRF module
#define mirf_CSN_hi     CSN_PORT |=  (1<<CSN);
#define mirf_CSN_lo     CSN_PORT &= ~(1<<CSN);
#define mirf_CE_hi      CE_PORT |=  (1<<CE);
#define mirf_CE_lo      CE_PORT &= ~(1<<CE);

// Public standart functions
extern void mirf_init();
extern void mirf_config();
extern void mirf_send(uint8_t * value, uint8_t len);
extern void mirf_set_RADDR(uint8_t * adr);
extern void mirf_set_TADDR(uint8_t * adr);
extern uint8_t mirf_data_ready();
extern void mirf_get_data(uint8_t * data);

// Public extended functions
extern void mirf_config_register(uint8_t reg, uint8_t value);
extern void mirf_read_register(uint8_t reg, uint8_t * value, uint8_t len);
extern void mirf_write_register(uint8_t reg, uint8_t * value, uint8_t len);

#if defined(mirf_ADDR_len == 3)
	#define	mirf_SETUP_AW	1
#else if defined(mirf_ADDR_len == 4)
	#define	mirf_SETUP_AW	2
#else
	#define	mirf_SETUP_AW	3
#endif

#endif
#endif /* _MIRF_H_ */

