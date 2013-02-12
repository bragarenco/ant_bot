#ifndef nrf24l01c
#define nrf24l01c

#include "nrf24l01.h"	  
#include "spi.h"			// MCU Specific
#include <util/delay.h>		// MCU Specific

#define	spi_rxtx(tx) spi_fast_shift(tx)
#define spi_csh()	{PORTB = PINB | (1<<PB0);}
#define spi_csl()	{PORTB = PINB & ~(1<<PB0);}

#define spi_cel()	{_CE_PORT |= (1<<_CE_PIN);}
#define spi_ceh()	{_CE_PORT &= ~(1<<_CE_PIN);}
//	spi_ceh();
uint8_t NRF24L01_ReadReg(uint8_t Reg) {
	uint8_t Result;

	spi_csl();
	spi_rxtx(Reg);
	Result = spi_rxtx(NOP);
	spi_csh();

	return Result;
}

uint8_t NRF24L01_WriteReg(uint8_t Reg, uint8_t Value) {
	uint8_t Result;

	spi_csl();
	Result = spi_rxtx(Reg);
	spi_rxtx(Value);
	spi_csh();

	return Result;
}

uint8_t NRF24L01_ReadRegBuf(uint8_t Reg, uint8_t *Buf, uint16_t Size) {
	uint16_t i;
	uint8_t Result;

	spi_csl();
	Result = spi_rxtx(Reg);

	for (i = 0; i < Size; i++) {
		Buf[i] = spi_rxtx(NOP);
	}

	spi_csh();

	return Result;
}

uint8_t NRF24L01_WriteRegBuf(uint8_t Reg, uint8_t *Buf, uint16_t Size) {
	uint16_t i;
	uint8_t Result;

	spi_csl();
	Result = spi_rxtx(Reg);

	for (i = 0; i < Size; i++) {
		spi_rxtx(Buf[i]);
	}
	spi_csh();

	return Result;
}
/*
 Returns the STATUS register

 @return STATUS Register
*/
uint8_t NRF24L01_Get_Status(void) {
	uint8_t Result;

	spi_csl();
	Result = spi_rxtx(NOP);
	spi_csh();

	return Result;
}

uint8_t NRF24L01_Get_CD(void) {
	return (NRF24L01_ReadReg(CD) & 1);
}

void NRF24L01_Set_Power(uint8_t Mode) {
	uint8_t Result;

	Result = (NRF24L01_ReadReg(CONFIG) & 0xFD); // Read Conf. Reg. AND Clear bit 1 (PWR_UP) and 7 (Reserved)
	NRF24L01_WriteReg(W_REGISTER | CONFIG, Result | Mode);
}
/*
 Select the radio channel

 @param CH = 0..125

*/
void NRF24L01_Set_CH(uint8_t CH) {
	NRF24L01_WriteReg(W_REGISTER | RF_CH, (CH & 0x7F)); // Clear bit 8
}

void NRF24L01_Set_ShockBurst(uint8_t Mode) {
	NRF24L01_WriteReg(W_REGISTER | SETUP_RETR, Mode);
	NRF24L01_WriteReg(W_REGISTER | EN_AA, Mode);
}

void NRF24L01_Set_Address_Width(uint8_t Width) {
	NRF24L01_WriteReg(W_REGISTER | SETUP_AW, (Width & 3) -2);
}

void NRF24L01_Set_Device_Mode(uint8_t Device_Mode) {
	uint8_t Result;
        
        Result = NRF24L01_ReadReg(CONFIG) & 0X7E; // Read Conf. Reg. AND Clear bit 0 (PRIM_RX) and 7 (Reserved)
	NRF24L01_WriteReg(W_REGISTER | CONFIG, Result | Device_Mode);
}

void NRF24L01_Set_RX_Pipe(uint8_t PipeNum, uint8_t *Address, uint16_t AddressSize, uint8_t PayloadSize) {
	uint8_t Result;

	Result = NRF24L01_ReadReg(EN_RXADDR);
	NRF24L01_WriteReg(W_REGISTER | EN_RXADDR, Result | (1 << PipeNum));

	NRF24L01_WriteReg(W_REGISTER | (RX_PW_P0 + PipeNum), PayloadSize);
	NRF24L01_WriteRegBuf(W_REGISTER | (RX_ADDR_P0 + PipeNum), Address, AddressSize);
}

void NRF24L01_Disable_All_Pipes(void) {
	NRF24L01_WriteReg(W_REGISTER | EN_RXADDR, 0);
}

uint8_t NRF24L01_Clear_Interrupts(void) {
	return NRF24L01_WriteReg(W_REGISTER | STATUS, _RX_DR | _TX_DS | _MAX_RT);
}

void NRF24L01_Set_TX_Address(uint8_t *Address, uint16_t Size) {
	NRF24L01_WriteRegBuf(W_REGISTER | TX_ADDR, Address, Size);
}

void NRF24L01_Flush_TX(void) {
	spi_csl();
	spi_rxtx(FLUSH_TX);
	spi_csh();
}

void NRF24L01_Flush_RX(void) {
	spi_csl();
	spi_rxtx(FLUSH_RX);
	spi_csh();
}

void NRF24L01_Init(uint8_t Device_Mode, uint8_t CH, uint8_t DataRate,
		uint8_t *Address, uint8_t Address_Width, uint8_t Size_Payload) {

	// Disable Enhanced ShockBurst
	NRF24L01_Set_ShockBurst(_ShockBurst_OFF);

	// RF output power in TX mode = 0dBm (Max.)
	// Set LNA gain
	NRF24L01_WriteReg(W_REGISTER | RF_SETUP, 0x07 | DataRate);

	NRF24L01_Set_Address_Width(Address_Width);

	NRF24L01_Set_RX_Pipe(0, Address, Address_Width, Size_Payload);

	NRF24L01_Set_CH(CH);

	NRF24L01_Set_TX_Address(Address, Address_Width); // Set Transmit address

	// Bits 4..6: Reflect interrupts as active low on the IRQ pin
	// Bit 3: Enable CRC
	// Bit 2: CRC 1 Byte
	// Bit 1: Power Up
	NRF24L01_WriteReg(W_REGISTER | CONFIG, 0x0A | Device_Mode);
        _delay_us(1500);
}

void NRF24L01_RF_TX(void) {
	spi_cel();
	spi_ceh();
	_delay_us(10);
	spi_cel();
}

void NRF24L01_Write_TX_Buf(uint8_t *Buf, uint16_t Size) {
	NRF24L01_WriteRegBuf(W_REGISTER | W_TX_PAYLOAD, Buf, Size);
}

void NRF24L01_Read_RX_Buf(uint8_t *Buf, uint16_t Size) {
	NRF24L01_ReadRegBuf(R_RX_PAYLOAD, Buf, Size);
}

void NRF24L01_Set_Interrupt_Out(NRF24L01_IRQ_mask_Typedef mask)
{
  uint8_t temp;
  temp=NRF24L01_ReadReg(CONFIG);
  NRF24L01_WriteReg(CONFIG, temp|mask);
}

void NRF24L01_Set_Rf_Power(RF_POWER_Typedef tx_pwr, RF_POWER_Typedef lna_gain)
{
  uint8_t temp;
  temp=NRF24L01_ReadReg(RF_SETUP);
  temp&= ~((1<<0)|(1<<1)|(1<<2));
  NRF24L01_WriteReg(RF_SETUP, temp|tx_pwr|lna_gain);
}

#endif //nrf24l01c
