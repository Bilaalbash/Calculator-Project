#include "PLL_1.h"
#include "LCD.h"
#include <stdio.h>
#include "UART.h"
#define lcdEN (*((volatile unsigned long *)0x40004020))
#define lcdRS (*((volatile unsigned long *)0x40004010))
#define lcdDB (*((volatile unsigned long *)0x400050F0))
	

unsigned char uppernibble, lowernibble, uppernibble2, uppernibble3, lowernibble3;
unsigned long PB;
unsigned long EN;



void lcdWriteChar(char c3){
	lcdRS = 0x04;								//set RS to high for command entry for data entry
	uppernibble3 = (c3&0xF0);		//Bit masking for only the upper nibble
	lowernibble3 = (c3&0x0F);		//Bit masking for only the lower nibble
	lcdDB = (uppernibble3>>2);	//Writing uppernibble to lcd, shifting two to the right for PB2-5
	lcdENpulse();								//Pulse EN line
	lcdDB = (lowernibble3<<2);	//Writing lowernibble to lcd, shifting two to the left for PB2-5 
	lcdENpulse();								//Pulse EN line
	SysTick_Wait_50ns(3000);		//Wait 150us
}

void lcdWriteHalfCommand(unsigned char c2){
	lcdRS = 0x00;								//set RS to 0 for command entry 
	uppernibble2 = (c2&0xF0);		//Bit masking for only the upper nibble
	lcdDB = (uppernibble2>>2);	//Writing uppernibble to lcd, shifting two to the right for PB2-5
	lcdENpulse();								//Pulse EN line
	SysTick_Wait_1us(4200);			//Wait 4.2ms
}

void lcdWriteCommand(unsigned char c){
	lcdRS = 0x00;								//set RS to 0 for command entry
	uppernibble = (c&0xF0);			//Bit masking for only the upper nibble
	lowernibble = (c&0x0F);			//Bit masking for only the lower nibble
	lcdDB = (uppernibble>>2);		//Writing uppernibble to lcd, shifting two to the right for PB2-5
	lcdENpulse();								//Pule EN line
	lcdDB = (lowernibble<<2);		//Writing lowernibble to lcd, shifting two to the left for PB2-5
	lcdENpulse();								//Pulse EN line
	SysTick_Wait_1us(3200);			//Wait 3.2ms
}

void lcd_Init(void){
	lcdEN = 0x00;								//clear EN
	lcdDB = 0x00;								//clear DB
	lcdRS = 0x00;								//clear RS
	SysTick_Wait_1us(100000);		//Wait 100ms
	lcdWriteHalfCommand(0x30);	//Send 0011 to DB
	lcdWriteHalfCommand(0x30);	//Send 0011 Again
	lcdWriteHalfCommand(0x30);	//Send 0011 Again
	lcdWriteHalfCommand(0x20);	//Send 0010 to set lcd to 4-bit mode
	lcdWriteCommand(0x28);			//Send 0010 followed by 1000 to lcd. Set to two Lines and Small font
	lcdWriteCommand(0x0C);			//Send 0000 followed by 1111 to turn display cursor and blinking on 
	lcdWriteCommand(0x01);			//Send 0000 followed by 0001 to clear display
	lcdWriteCommand(0x06);			//Send 0000 followed by 0110 to set Increment on

	//Initilalization over
	
}
void lcdENpulse(void){
	lcdEN = 0x08;								//set EN as high
	SysTick_Wait_50ns(20); 			//Delay 1us
	lcdEN = 0x00;								//clear EN
}

void lcdClearScreen(void){				
	lcdWriteCommand(0x01);			//Pulse EN line
}

void lcdWriteString (char *string) {
	while(*string){							//While loop for writing string
		lcdWriteChar(*string);		//Send String to lcd
		string++;									//Increment string
	}
}
