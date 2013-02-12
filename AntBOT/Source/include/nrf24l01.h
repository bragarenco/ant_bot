#ifndef nrf24l01
#define nrf24l01

#include	<inttypes.h>
#include	<avr/io.h>

#define _RX_DR        (1<<6) // data received interrupt flag
#define _TX_DS        (1<<5) // data sent interrupt flag
#define _MAX_RT       (1<<4) // Maximum number of TX retransmits interrupt
#define _POWER_DOWN     0    // Minimal current consumption, SPI is active
#define _POWER_UP     (1<<1) // go to Standby-I mode
#define _TX_MODE	0    // to PRIM_RX bit from CONFIG
#define _RX_MODE	1    // to PRIM_RX bit from CONFIG
#define	_1Mbps	        0    //  Air data rate = 1 Mbps
#define	_2Mbps	      (1<<3) // Air data rate = 2 Mbps
#define _ShockBurst_ON  1    // Automatic Retransmission CRC etc.
#define _ShockBurst_OFF 0    //  Disable ShockBurst

#define _CE_DDR		DDRE
#define _CE_PORT	PORTE
#define _CE_PIN		PE7

#define _CSN_DDR	DDRB
#define _CSN_PORT	PORTB
#define _CSN_PIN	PB0

#define _CE_HI()	{_CE_PORT |= (1<<_CE_PIN);}
#define _CE_LO()	{_CE_PORT &= ~(1<<_CE_PIN);}


#define IRQ_DDR()	(DDRE &= ~(1<<PE6))
#define nrf_IRQ()	!(PINE & (1<<PE7))

// REGISTERS addresses 
typedef enum NRF24L01_register_map
	{
	 CONFIG		=	0x00,
	 EN_AA		=	0x01,
	 EN_RXADDR	=	0x02,
	 SETUP_AW	=	0x03,
	 SETUP_RETR	=	0x04,
	 RF_CH		=	0x05,
	 RF_SETUP	=	0x06,
	 STATUS		=	0x07,
	 OBSERVE_TX	=	0x08,
	 CD		=	0x09,
	 RX_ADDR_P0	=	0x0A,
	 RX_ADDR_P1	=	0x0B,
	 RX_ADDR_P2	=	0x0C,
	 RX_ADDR_P3	=	0x0D,
	 RX_ADDR_P4	=	0x0E,
	 RX_ADDR_P5	=	0x0F,
	 TX_ADDR	=	0x10,
	 RX_PW_P0	=	0x11,
	 RX_PW_P1	=	0x12,
	 RX_PW_P2	=	0x13,
	 RX_PW_P3	=	0x14,
	 RX_PW_P4	=	0x15,
	 RX_PW_P5	=	0x16,
	 FIFO_STATUS	=	0x17,
	 DYNPD		=	0x1C,
	 FEATURE	=	0x1D
	}NRF24L01_register_map_Typedef;

// PA output power and LNA gain.  _mXXdBm means minusXXdBm
typedef enum RF_POWER
{
      TX_PWR_m18dBm     =       (0<<2)|(0<<1),
      TX_PWR_m12dBm     =       (0<<2)|(1<<1),
      TX_PWR_m6dBm      =       (1<<2)|(0<<1),
      TX_PWR_0dBm       =       (1<<2)|(1<<1),
      LNA_MAX_GAIN      =       (0<<0),
      LNA_MIN_GAIN      =       (1<<0)
}RF_POWER_Typedef;

// COMMANDS for nrf24l01 core
typedef enum NRF_COMMANDS
	{
	 R_REGISTER	    = 0x00, //Read command and status reg.000AAAAA =
				    //5 bit Register Map Address
	 W_REGISTER	    = 0x20, //Write command and status reg.000AAAAA =
				    //5 bit Register Map Address
	 R_RX_PAYLOAD	    = 0x61, //Read RX-payload: 1 – 32 bytes.
				    //Starts at byte 0. Payload is deleted from
				    //FIFO after it is read. Used in RX mode.
	 W_TX_PAYLOAD	    = 0xA0, //Write TX-payload: 1 – 32 bytes.
  				    //Starts at byte 0 used in TX payload.
	 FLUSH_TX	    = 0xE1, //Flush TX FIFO, used in TX mode
	 FLUSH_RX	    = 0xE2, //Flush RX FIFO, used in RX mode
				    //Shouldn't be executed during transmission
				    //of  ACK, that is, ACK package will
				    //not be completed.
	 REUSE_TX_PL	    = 0XE3, //Used for a PTX device
			//Reuse last transmitted payload. Packets are
			//repeatedly retransmitted as long as CE is high.
			//TX payload reuse is active until
			//W_TX_PAYLOAD or FLUSH TX is executed. TX
			//payload reuse must not be activated or
			//deacti-vated during package transmission
	 ACTIVATE           = 0X50, /*This write command followed by data 0x73
                        acti-vates the following features:
			  • R_RX_PL_WID
			  • W_ACK_PAYLOAD
			  • W_TX_PAYLOAD_NOACK
			A new ACTIVATE command with the same data
			deactivates them again. This is executable in
			power down or stand by modes only.
			The R_RX_PL_WID, W_ACK_PAYLOAD, and
			W_TX_PAYLOAD_NOACK features registers are
			initially in a deactivated state; a write has no
			effect, a read only results in zeros on MISO. To
			activate these registers, use the ACTIVATE command
                        followed by data 0x73. Then they can be
			accessed as any other register in nRF24L01. Use
			the same command and data to deactivate the
			registers again.*/
	R_RX_PL_WID         = 0x60, //Read RX-payload width for the top
				    //R_RX_PAYLOAD in the RX FIFO.
	W_ACK_PAYLOAD	    = 0xA8, /*Used in RX mode.
			Write Payload to be transmitted together with
			ACK packet on PIPE PPP. (PPP valid in the
			range from 000 to 101). Maximum three ACK
			packet payloads can be pending. Payloads with
			same PPP are handled using first in - first out
			principle. Write payload: 1– 32 bytes. A write
			operation always starts at byte 0.*/
	W_TX_PAYLOAD_NOACK  = 0xB0, //Used in TX mode. Disables AUTOACK on this
				    //specific packet.
	NOP		    = 0xFF  //NOP. Might be used to read the STATUS reg.
	}NRF_COMMANDS_Typedef;

// masks for interrupts MASKed one is disabled.
// interrupt flag is active but it is not shown on IRQ pin

typedef enum NRF24L01_IRQ_mask
{
  MASK_RX_DR      = (1<<6),
  MASK_TX_DS      = (1<<5),
  MASK_MAX_RT     = (1<<4),
  MASK_ALL        =  MASK_RX_DR|MASK_TX_DS|MASK_MAX_RT,
  MASK_NONE       = 0x00
}NRF24L01_IRQ_mask_Typedef;

// SPI functions for NRF24L01

uint8_t NRF24L01_ReadReg(uint8_t Reg);
uint8_t NRF24L01_WriteReg(uint8_t Reg, uint8_t Value);
uint8_t NRF24L01_ReadRegBuf(uint8_t Reg, uint8_t *Buf, uint16_t Size);
uint8_t NRF24L01_WriteRegBuf(uint8_t Reg, uint8_t *Buf, uint16_t Size);

//NRF24L01 functions

uint8_t NRF24L01_Get_Status(void);
uint8_t NRF24L01_Get_CD(void);
void NRF24L01_Set_Power(uint8_t Mode);
void NRF24L01_Set_CH(uint8_t CH);
void NRF24L01_Set_ShockBurst(uint8_t Mode);
void NRF24L01_Set_Address_Width(uint8_t Width);
void NRF24L01_Set_Device_Mode(uint8_t Device_Mode);
void NRF24L01_Set_RX_Pipe(uint8_t PipeNum, uint8_t *Address, 
                          uint16_t AddressSize, uint8_t PayloadSize);
void NRF24L01_Disable_All_Pipes(void);
uint8_t NRF24L01_Clear_Interrupts(void);
void NRF24L01_Set_TX_Address(uint8_t *Address, uint16_t Size);
void NRF24L01_Flush_TX(void);
void NRF24L01_Flush_RX(void);
void NRF24L01_Init(uint8_t Device_Mode, uint8_t CH, uint8_t DataRate,
		uint8_t *Address, uint8_t Address_Width, uint8_t Size_Payload);
void NRF24L01_RF_TX(void);
void NRF24L01_Write_TX_Buf(uint8_t *Buf, uint16_t Size);
void NRF24L01_Read_RX_Buf(uint8_t *Buf, uint16_t Size);
void NRF24L01_Set_Rf_Power(RF_POWER_Typedef tx_pwr, RF_POWER_Typedef lna_gain);
void NRF24L01_Set_Interrupt_Out(NRF24L01_IRQ_mask_Typedef mask);

#endif// nrf24l01
