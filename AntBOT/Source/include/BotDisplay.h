/*
 * BotDisplay.h
 *
 *  Created on: Dec 20, 2012
 *      Author: Andrei
 */

#ifndef BOT_DISPLAY_H_
#define BOT_DISPLAY_H_

#include <avr/io.h>

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
#define	LCD_BUSY				LCD_D7


void LCD_PortInit(){
	LCD_DDR  = 0x0E;
	LCD_PORT = 0xF0;
}


void LCD_Delay(char cnt){
	//7. Pauza
	for(char i= 0; i< cnt; i++){
		asm(" nop");
	}
}

void LCD_SetDataAsInput(){
//1. Data input , pull-up
	LCD_DDR  &= ~((1<<LCD_D4) + (1<<LCD_D5) + (1<<LCD_D6) + (1<<LCD_D7));
	LCD_PORT |=  ((1<<LCD_D4) + (1<<LCD_D5) + (1<<LCD_D6) + (1<<LCD_D7));
}

void LCD_SetDataAsOutput(){
//1. Data Output
	LCD_DDR  |= ( (1<<LCD_D4) + (1<<LCD_D5) + (1<<LCD_D6) + (1<<LCD_D7));
}


void LCD_ClearDataPort(){
//1. CLEAR Data Output
	LCD_PORT &=  ~((1<<LCD_D4) + (1<<LCD_D5) + (1<<LCD_D6) + (1<<LCD_D7));
}

void LCD_SetLowNibble(char command){
	LCD_PORT &=  ~((1<<LCD_D4) + (1<<LCD_D5) + (1<<LCD_D6) + (1<<LCD_D7));
	LCD_PORT |=  (command<<4) & 0xF0;
}

void LCD_SetHighNibble(char command){
	LCD_PORT &=  ~((1<<LCD_D4) + (1<<LCD_D5) + (1<<LCD_D6) + (1<<LCD_D7));
	LCD_PORT |= command & 0xF0;
}

void LCD_GetLowNibble(char *data){
	*data &= 0xF0;
	*data |= (LCD_PIN>>4)&0x0F;
}

void LCD_GetHighNibble(char *data){
	*data &= 0x0F;
	*data |= (LCD_PIN)&0xF0;
}



void LCD_RS_ToLow(){
	//2. RS = 0
    LCD_DDR  |=  (1<<LCD_RS);
    LCD_PORT &= ~(1<<LCD_RS);
}

void LCD_RS_ToHigh(){
	//2. RS = 0
    LCD_DDR  |=  (1<<LCD_RS);
    LCD_PORT |=  (1<<LCD_RS);
}

void LCD_RW_ToLow(){
	//2. RW = 0
    LCD_DDR  |=  (1<<LCD_RW);
    LCD_PORT &= ~(1<<LCD_RW);
}

void LCD_RW_ToHigh(){
	//2. RW = 0
    LCD_DDR  |=  (1<<LCD_RW);
    LCD_PORT |=  (1<<LCD_RW);
}

void LCD_E_ToLow(){
	//2. E = 0
    LCD_DDR  |=  (1<<LCD_E);
    LCD_PORT &= ~(1<<LCD_E);
}

void LCD_E_ToHigh(){
	//2. E = 0
    LCD_DDR  |=  (1<<LCD_E);
    LCD_PORT |=  (1<<LCD_E);
}

char  LCD_BF_IsSet(){
	return ( LCD_PIN & (1<<LCD_D7));
}

void LCD_WriteNibble(char nibble){

}


void LCD_WriteByte(char byte){


	//5. Port date spre iesire
	LCD_SetDataAsOutput();

	//3. RW = 0 (scriere)
    LCD_RW_ToLow();

	//3. Pauza
	LCD_Delay(5);

	//1. E = 1
    LCD_E_ToHigh();

	//2. Setarea pe port a codului comenzii - tetrada superioara.
	LCD_SetHighNibble(byte);

	//3. Pauza
	LCD_Delay(5);

	//4. E = 0 (datele sunt transferate in dispozitiv pe frontul descrescator)
    LCD_E_ToLow();

	//5. Pauza
	LCD_Delay(5);

	//6. E = 1
    LCD_E_ToHigh();

	//7. Setarea pe port a codului comenzii - tetrada inferioara
	LCD_SetLowNibble(byte);

	//8. Pauza
	LCD_Delay(5);

	//9. E = 0 (datele sunt transferate in dispozitiv pe frontul descrescator)
    LCD_E_ToLow();

	//9. Restabilire portului de date pe intrare
	LCD_SetDataAsInput();

}

char LCD_ReadByte(){
	char byte;


	//2. Data input , pull-up
	LCD_SetDataAsInput();

	//3. RW = 1 (citire)
    LCD_RW_ToHigh();

	//1. E = 1 (Datele sunt transferate din LCD pe frontul crescator)
     LCD_E_ToHigh();

	//3. Pauza
	LCD_Delay(5);

	//2. Culegerea de pe port  tetrada superioara.
	LCD_GetHighNibble(&byte);

	//4. E = 0
    LCD_E_ToLow();

	//5. Pauza
	LCD_Delay(2);

	//6. E = 1 (Datele sunt transferate din LCD pe frontul crescator)
    LCD_E_ToHigh();

	//8. Pauza
	LCD_Delay(5);

	//7. Culegerea de pe port tetrada inferioara
	LCD_GetLowNibble(&byte);

	//9. E = 0
    LCD_E_ToLow();

	//9. Restabilire portului de date pe intrare
	LCD_SetDataAsInput();

	return byte;
}

// wait until busy flag is cleared
void LCD_WaitBussy(){

char byte;

do{
	//1. Data input , pull-up
	LCD_SetDataAsInput();

	//2. RS = 0 command register
 	LCD_RS_ToLow();

	//5. wait few cycles
	LCD_Delay(2);

	//3. RW = 1 read
    LCD_RW_ToHigh();

	}
	while ( (byte = LCD_ReadByte()) & (1<<LCD_BUSY));

}

// Write command
void LCD_WriteCommand( char command){

	//1. Wait device
	LCD_WaitBussy();

	//2. RS = 0   (registru de comenzi)
    LCD_RS_ToLow();

	// scrie data
	LCD_WriteByte(command);

}


// Read Command
char LCD_ReadCommand(){

	char data;

	//1. Wait device
	LCD_WaitBussy();

	//2. RS = 0   (registru de comenzi)
    LCD_RS_ToLow();

	// citeste data data
	data = LCD_ReadByte();

	return data;
}



// Write Data
void LCD_WriteData( char data ){

	//1. Wait device
	LCD_WaitBussy();

	//2. RS = 1   (registru de date)
    LCD_RS_ToHigh();

	// scrie data
	LCD_WriteByte(data);

}

// Read Data
char LCD_ReadData(){

	char data;

	//1. Wait device
	LCD_WaitBussy();

	//3. RS = 1   (registru de date)
    LCD_RS_ToHigh();

	// citeste data data
	data = LCD_ReadByte();

	return data;
}





void LCD_Init(){

	LCD_PortInit();

	LCD_WriteCommand(0b00101000); //-   Bus-ul de date pe 4 biti, afisare in 2 randuri.
	LCD_WriteCommand(0b00000001); //-   Curatarea ecranului
	LCD_WriteCommand(0b00000110); //-   Incrementarea adresei la fiecare acces, Ecranul nu se deplaseaza.

}

LCD_PrintLogo(){
	LCD_WriteCommand(0b00001100); //- Aprinde ecran (D=1)
	LCD_WriteCommand(0b00000001); //- Curatare ecran, Memoria DDRAM este selectata
	LCD_WriteCommand(0b00010100); //- Deplasare cursor (S/C=0) la dreapta (R/L=1)
	LCD_WriteData(0b00110001); //- Transfer in memeoria DDRAM (RS=1) a caracterului "1?, cod 0?31
}






#endif /* BOT_DISPLAY_H_ */
