// This is your first program to run on the LaunchPad
// You will run this program without modification as your Lab 2
// If the left switch SW1 is 
//      not pressed the LED toggles blue-red
//      pressed the LED toggles blue-green
#include <stdio.h>
#include "LCD.h"
#include "Init.h"
#include "PLL_1.h"
#include "UART.h"
#include "Keypad.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))

// 1. Pre-processor Directives Section
// Constant declarations to access port registers using 
// symbolic names instead of addresses

// 2. Declarations Section
//   Global Variables
unsigned long In;  // input from PF4
int PIN;
int ExpectedPIN;
int PINEntered;
float F_Value;
float S_Value;
float T_Value;
float Temp_Value;
float Total_Value;
int Limit_Reached;
float Value;
unsigned char input;
unsigned char input2;
unsigned char input3;
char TString[50];

//   Function Prototypes
void All_Init(void);
void Request_PIN(void);
void Calculations(void);
float Get_Value(float input0);
void Reset_Calc(void);
void Calc_Test(void);
void Loading_Screen(int seconds);
void Loading_Screen2(int seconds);

// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable
int main(void){    
	All_Init();
	Request_PIN();
	Loading_Screen2(1);
//	Loading_Screen(5);
  while(1){
		//Calc_Test();
		Calculations();
  }
}


void All_Init(void){
	PortF_init();
	PortA_init();
	PortB_init();
	PortD_init();
	PortE_init();
	PLL_Init();
	SysTick_Init();
	UART_Init();
	lcd_Init();
	Keypad_Init();
	ExpectedPIN = 1996;
	PINEntered = 0;
	PIN = 0;
	Total_Value = 0;
	input2 = 0;
}

void Loading_Screen2(int seconds){
	unsigned long i;
	for (i=0;i<seconds;i++){
	lcdWriteCommand(0x02);
		lcdWriteString("a              d");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString("oa            di");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString("Loa          din");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString(" Loa        ding");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString("  Loa      ding ");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString("   Loa    ding  ");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString("    Loa  ding   ");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString("     Loading    ");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString("     Loading.   ");
		SysTick_Wait_1us(250000);
		lcdWriteCommand(0x02);
		lcdWriteString("     Loading..  ");
		SysTick_Wait_1us(250000);
		lcdWriteCommand(0x02);
		lcdWriteString("     Loading... ");
		SysTick_Wait_1us(250000);
		lcdWriteCommand(0x02);
		lcdWriteString("     Loading    ");
		SysTick_Wait_1us(250000);
		lcdWriteCommand(0x02);
		lcdWriteString("     Loading.   ");
		SysTick_Wait_1us(250000);
		lcdWriteCommand(0x02);
		lcdWriteString("     Loading..  ");
		SysTick_Wait_1us(250000);
		lcdWriteCommand(0x02);
		lcdWriteString("     Loading... ");
		SysTick_Wait_1us(250000);
		lcdWriteCommand(0xC0);
		lcdWriteString("       <>       ");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0xC0);
		lcdWriteString("      <-->      ");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0xC0);
		lcdWriteString("     <---->     ");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0xC0);
		lcdWriteString("    <------>    ");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0xC0);
		lcdWriteString("   <-------->   ");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0xC0);
		lcdWriteString("  <---------->  ");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0xC0);
		lcdWriteString(" <------------> ");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0xC0);
		lcdWriteString("<-------------->");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0xC0);
		lcdWriteString("<------W!------>");
		SysTick_Wait_1us(250000);
		lcdWriteCommand(0xC0);
		lcdWriteString("<-----Wee!----->");
		SysTick_Wait_1us(250000);
		lcdWriteCommand(0xC0);
		lcdWriteString("<----Welme!---->");
		SysTick_Wait_1us(250000);
		lcdWriteCommand(0xC0);
		lcdWriteString("<---Welcome!--->");
		SysTick_Wait_1us(2500000);
		lcdClearScreen();
	}
}

void Loading_Screen(int seconds){
		unsigned long i;
	for (i=0;i<seconds;i++){
		lcdWriteCommand(0x02);
		lcdWriteString("Calculator (:+})");
		lcdWriteCommand(0xC0);
		lcdWriteString("Loading");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString("Calculator (;+})");
		lcdWriteCommand(0xC0);
		lcdWriteString("Loading.");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString("Calculator (:+})");
		lcdWriteCommand(0xC0);
		lcdWriteString("Loading..");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString("Calculator (;+})");
		lcdWriteCommand(0xC0);
		lcdWriteString("Loading...");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString("Calculator (:+})");
		lcdWriteCommand(0xC0);
		lcdWriteString("Loading....");
		SysTick_Wait_1us(200000);
		lcdWriteCommand(0x02);
		lcdWriteString("Calculator (;+})");
		lcdWriteCommand(0xC0);
		lcdWriteString("Loading.....");
		SysTick_Wait_1us(200000);
		lcdClearScreen();
	}
}

void Request_PIN(void){
	while(PIN != ExpectedPIN){
			lcdClearScreen();
			lcdWriteCommand(0x02);
			lcdWriteString("Please Enter PIN");
			ResetAnswer();
			lcdWriteCommand(0xC0);
			while (PINEntered == 0){
				readKeypad();
				PIN = Answer;
				if (Answer > 999){
					PINEntered = 1;
				}
			}
			if (PIN == ExpectedPIN){
				lcdClearScreen();
				lcdWriteCommand(0x02);
				lcdWriteString("PIN Correct!");
				lcdWriteCommand(0xC0);
//				lcdWriteString("Welcome");
				SysTick_Wait_1us(2000000);
				ResetAnswer();
				lcdClearScreen();
			}
			else if (PIN != ExpectedPIN){
				lcdClearScreen();
				lcdWriteCommand(0x02);
				lcdWriteString("PIN Incorrect!");
				lcdWriteCommand(0xC0);
				lcdWriteString("Please try again");
				SysTick_Wait_1us(2000000);
				ResetAnswer();
				lcdClearScreen();
				PIN = 0;
				PINEntered = 0;
				Limit_Reached = 0;
				input = 0;
				input3 = 0;
			}
		}
		lcdWriteCommand(0x0F); 		//Turn Cursor and Blinking back on
}

void Calculations(){
	input = readKeypad();
	printf("\n\n\n CALCULATIONS RUNNING \n\n\n");
	if(input == 'G' || input == '#'){
	input = input3;
	}

	switch(input){
		case 'A':				//'+' Operation
			printf("\n Case = A Operand = + ||\n");
			Value = 0;
			S_Value = Get_Value(0);
			Value = 0;
			Total_Value = F_Value + S_Value;
			printf("\n First Value = %f",F_Value);
			printf("\n Second Value = %f",S_Value);
			input2 = input3;
					
			switch(input2){
				case 'A':					//'+' Operation	
				
				printf("\n Case = AA Operand = + || + ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
				Total_Value = F_Value + S_Value + T_Value;
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);		
				
				break;
		
				case 'B':									//'-' Operation
					
				printf("\n Case = AB Operand = + || - ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
				Total_Value = F_Value + S_Value - T_Value;
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);					
				
				break;
				
				case 'C':									//'*' Operation
					
				printf("\n Case = AC Operand = + || * ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
				Total_Value = F_Value + (S_Value * T_Value);
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);
				
				break;
				
				case 'D':									//'/' Operation
					
				printf("\n Case = AD Operand = + || / ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
					
				if (T_Value == 0){
					lcdWriteCommand(0x02);
					lcdWriteString("INVALID ENTRY");
					lcdWriteCommand(0xC0);
					lcdWriteString("RESETTING...");
					SysTick_Wait_1us(3000000);
					Reset_Calc();
				}
					
				Total_Value = F_Value + (S_Value / T_Value);
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);	
				
				break;
				
				case '#':									//'=' Operation
					
				printf("\n Case = A= Operand = + || = ||\n");
					
				if(Total_Value!= 0){
					lcdClearScreen();
					sprintf(TString,"%g",Total_Value);			// Turn Answer variable into a String
					lcdWriteCommand(0xC0);						//Set to second line
					lcdWriteString(TString);
					lcdWriteCommand(0x02);
					F_Value = 0;
					S_Value = 0;
					Value = 0;
				}				
						
				input = 0;
				input2 = 0;
			
				break;
				
				case '*':						//clear Operation
				
				printf("\n Case = Clear Screen\n");	
				Reset_Calc();
				Limit_Reached = 1;
				
				break;
					
				case '0': case '1': case '2': case '3': case '4': case'5': case '6': case'7': case '8': case '9':						//Number Entry
				
				printf("\n Case = Ainput Operand = + || IN ||\n");
				S_Value = Get_Value(input2);
				if (input3 == 'A' ||input3 =='B' ||input3 == 'C' || input3 == 'D' || input3 == '#' ||input3 == '*' ){
						input3 = input2;
					}
				
				break;
	}
			break;

		case 'B':				//'-' Operation
			printf("\n Case = B Operand = - ||\n");
			Value = 0;
			S_Value = Get_Value(0);
			Value = 0;
			Total_Value = F_Value - S_Value;
			printf("\n First Value = %f",F_Value);
			printf("\n Second Value = %f",S_Value);
			input2 = input3;
					
			switch(input2){
				case 'A':					//'+' Operation	
				
				printf("\n Case = BA Operand = - || + ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
				Total_Value = F_Value - S_Value + T_Value;
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);		
				
				break;
		
				case 'B':									//'-' Operation
					
				printf("\n Case = BB Operand = - || - ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
				Total_Value = F_Value - S_Value - T_Value;
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);					
				
				break;
				
				case 'C':									//'*' Operation
					
				printf("\n Case = BC Operand = - || * ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
				Total_Value = F_Value - (S_Value * T_Value);
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);
				
				break;
				
				case 'D':									//'/' Operation
					
				printf("\n Case = BD Operand = - || / ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
					
				if (T_Value == 0){
					lcdWriteCommand(0x02);
					lcdWriteString("INVALID ENTRY");
					lcdWriteCommand(0xC0);
					lcdWriteString("RESETTING...");
					SysTick_Wait_1us(3000000);
					Reset_Calc();
				}
					
				Total_Value = F_Value - (S_Value / T_Value);
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);	
				
				break;
				
				case '#':									//'=' Operation
					
				printf("\n Case = B= Operand = - || = ||\n");
					
				if(Total_Value!= 0){
					lcdClearScreen();
					sprintf(TString,"%g",Total_Value);			// Turn Answer variable into a String
					lcdWriteCommand(0xC0);						//Set to second line
					lcdWriteString(TString);
					lcdWriteCommand(0x02);
					F_Value = 0;
					S_Value = 0;
					Value = 0;
				}				
						
				input = 0;
				input2 = 0;
			
				break;
				
				case '*':						//clear Operation
				
				printf("\n Case = Clear Screen\n");	
				Reset_Calc();
				
				break;
					
				case '0': case '1': case '2': case '3': case '4': case'5': case '6': case'7': case '8': case '9':						//Number Entry
				
				printf("\n Case = Ainput Operand = - || IN ||\n");
				S_Value = Get_Value(input2);
				if (input3 == 'A' ||input3 =='B' ||input3 == 'C' || input3 == 'D' || input3 == '#' ||input3 == '*' ){
					input3 = input2;
				}
				
				break;
	}
			break;

		case 'C':				//'*' Operation
			printf("\n Case = C Operand = * ||\n");
			Value = 0;
			S_Value = Get_Value(0);
			Value = 0;
			Total_Value = F_Value + S_Value;
			printf("\n First Value = %f",F_Value);
			printf("\n Second Value = %f",S_Value);
			input2 = input3;
					
			switch(input2){
				case 'A':					//'+' Operation	
				
				printf("\n Case = CA Operand = * || + ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
				Total_Value = (F_Value * S_Value) + T_Value;
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);		
				
				break;
		
				case 'B':									//'-' Operation
					
				printf("\n Case = CB Operand = * || - ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
				Total_Value = (F_Value * S_Value) - T_Value;
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);					
				
				break;
				
				case 'C':									//'*' Operation
					
				printf("\n Case = CC Operand = * || * ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
				Total_Value = F_Value * S_Value * T_Value;
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);
				
				break;
				
				case 'D':									//'/' Operation
					
				printf("\n Case = CD Operand = * || / ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
					
				if (T_Value == 0){
					lcdWriteCommand(0x02);
					lcdWriteString("INVALID ENTRY");
					lcdWriteCommand(0xC0);
					lcdWriteString("RESETTING...");
					SysTick_Wait_1us(3000000);
					Reset_Calc();
				}
					
				Total_Value = (F_Value * S_Value) / T_Value;
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);	
				
				break;
				
				case '#':									//'=' Operation
					
				printf("\n Case = C= Operand = * || = ||\n");
					
				if(Total_Value!= 0){
					lcdClearScreen();
					sprintf(TString,"%g",Total_Value);			// Turn Answer variable into a String
					lcdWriteCommand(0xC0);						//Set to second line
					lcdWriteString(TString);
					lcdWriteCommand(0x02);
					F_Value = 0;
					S_Value = 0;
					Value = 0;
				}				
						
				input = 0;
				input2 = 0;
			
				break;
				
				case '*':						//clear Operation
				
				printf("\n Case = Clear Screen\n");	
				Reset_Calc();
				Limit_Reached = 1;
				
				break;
					
				case '0': case '1': case '2': case '3': case '4': case'5': case '6': case'7': case '8': case '9':						//Number Entry
				
				printf("\n Case = Ainput Operand = * || IN ||\n");
				S_Value = Get_Value(input2);
				if (input3 == 'A' ||input3 =='B' ||input3 == 'C' || input3 == 'D' || input3 == '#' ||input3 == '*' ){
						input3 = input2;
					}
				
				break;
	}
			break;

		case 'D':				//'/' Operation
			printf("\n Case = D Operand = / ||\n");
			Value = 0;
			S_Value = Get_Value(0);
			Value = 0;
			Total_Value = F_Value / S_Value;
			printf("\n First Value = %f",F_Value);
			printf("\n Second Value = %f",S_Value);
			input2 = input3;
					
			switch(input2){
				case 'A':					//'+' Operation	
				
				printf("\n Case = DA Operand = / || + ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
				Total_Value = (F_Value / S_Value) + T_Value;
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);		
				
				break;
		
				case 'B':									//'-' Operation
					
				printf("\n Case = DB Operand = / || - ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
				Total_Value = (F_Value / S_Value) - T_Value;
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);					
				
				break;
				
				case 'C':									//'*' Operation
					
				printf("\n Case = DC Operand = / || * ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
				Total_Value = (F_Value / S_Value) * T_Value;
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);
				
				break;
				
				case 'D':									//'/' Operation
					
				printf("\n Case = DD Operand = / || / ||\n");
				T_Value = Get_Value(0);
				input2 = input3;
				Value = 0;
					
				if (T_Value == 0){
					lcdWriteCommand(0x02);
					lcdWriteString("INVALID ENTRY");
					lcdWriteCommand(0xC0);
					lcdWriteString("RESETTING...");
					SysTick_Wait_1us(3000000);
					Reset_Calc();
				}
					
				Total_Value = (F_Value / S_Value) / T_Value;
				printf("\n First Value = %f",F_Value);
				printf("\n Second Value = %f",S_Value);
				printf("\n Third Value = %f",T_Value);
				printf("\n Total Value = %f",Total_Value);	
				
				break;
				
				case '#':									//'=' Operation
					
				printf("\n Case = D= Operand = / || = ||\n");
					
				if(Total_Value!= 0){
					lcdClearScreen();
					sprintf(TString,"%g",Total_Value);			// Turn Answer variable into a String
					lcdWriteCommand(0xC0);						//Set to second line
					lcdWriteString(TString);
					lcdWriteCommand(0x02);
					F_Value = 0;
					S_Value = 0;
					Value = 0;
				}				
						
				input = 0;
				input2 = 0;
			
				break;
				
				case '*':						//clear Operation
				
				printf("\n Case = Clear Screen\n");	
				Reset_Calc();
				Limit_Reached = 1;
				
				break;
					
				case '0': case '1': case '2': case '3': case '4': case'5': case '6': case'7': case '8': case '9':						//Number Entry
				
				printf("\n Case = Ainput Operand = / || IN ||\n");
				S_Value = Get_Value(input2);
				if (input3 == 'A' ||input3 =='B' ||input3 == 'C' || input3 == 'D' || input3 == '#' ||input3 == '*' ){
						input3 = input2;
					}
				
				break;
	}
			break;

			case '#':									//'=' Operation
			
			printf("\n Case = = Operand = = || \n");
			printf("\nFinal =");
			lcdClearScreen();
		
			if(Total_Value!= 0){
				lcdWriteCommand(0xC0);
				sprintf(TString,"%g",Total_Value);			// Turn Answer variable into a String
				lcdWriteCommand(0xC0);						//Set to second line
				lcdWriteString(TString);
			}
			
			lcdWriteCommand(0x02);
			input = 0;
			input2 = 0;
			input3 = 0;
			F_Value = 0;
			S_Value = 0;
			T_Value = 0;
			Total_Value = 0;
			
			break;
			
			case '*':									//clear Operation
			
			printf("\n Case = Clear Screen ||\n");
			Reset_Calc();
			input3 = 0;
			
			break;
			
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:						//Number Entry
			
			printf("\n Case = input Operand = IN ||\n");
			F_Value = Get_Value(0);
			
			break;
			
		}
}

float Get_Value(float input0){
	while	(1){
		input2=readKeypad();
		while (input2 == 'G'){
			input2=readKeypad();
		}
		
		while(input2 >=0 && input2 <= 9){
			if (Value == 0) {
				Value += input2;
				}
				else if (Value != 0)
				{
				Value = (Value * 10);
				Value+= input2;
				}
				input2 = readKeypad();
			}
		if (input2 == 'A' ||input2 =='B' ||input2 == 'C' || input2 == 'D' 
					|| input2 == '#' ||input2 == '*' ){
						input3 = input2;
		
				printf("GET VALUE RUNNING");
				break;
}	
			
		}
return Value;
}

void Reset_Calc(void){
	lcdClearScreen();
	F_Value = 0;
	S_Value = 0;
	T_Value = 0;
	Total_Value = 0;
	input = 0;
	input2 = 0;
	Value = 0;
	input3 = 'H';

}

void Calc_Test(void){	
	switch(input2){
					case 'A':						//'+' Operation	
					printf("\n Case = A Operand = + ||\n");
					S_Value = Get_Value(0);
					Value = 0;
					printf("\n First Value = %f",F_Value);
					printf("\n Second Value = %f",S_Value);
					Total_Value = F_Value + S_Value;
					printf("\n Total Value = %f",Total_Value);
					break;
					case 'B':									//'-' Operation
					printf("\n Case = B Operand = - ||\n");
					S_Value = Get_Value(0);
					printf("\n First Value = %f",F_Value);
					printf("\n Second Value = %f",S_Value);
					Total_Value = F_Value - S_Value;
					printf("\n Total Value = %f",Total_Value);
					break;
					case 'C':									//'*' Operation
					printf("\n Case = C Operand = * ||\n");
					S_Value = Get_Value(0);
					printf("\n First Value = %f",F_Value);
					printf("\n Second Value = %f",S_Value);
					Total_Value = F_Value * S_Value;
					printf("\n Total Value = %f",Total_Value);
					break;
					case 'D':									//'/' Operation
					printf("\n Case = D Operand = / ||\n");
					S_Value = Get_Value(0);
					printf("\n First Value = %f",F_Value);
					printf("\n Second Value = %f",S_Value);
			
					if (S_Value == 0){
						lcdClearScreen();
						lcdWriteString("INVALID ENTRY");
						lcdWriteCommand(0xC0);
						lcdWriteString("RESETTING...");
						SysTick_Wait_1us(3000000);
						Limit_Reached = 1;
						Reset_Calc();
					}
					Total_Value = F_Value / S_Value;
					printf("\n Total Value = %f",Total_Value);
					break;
					case '#':									//'=' Operation
					printf("\n Case = = Operand = = ||\n");
					//S_Value = Get_Value(0);
					printf("\n First Value = %f",F_Value);
					printf("\n Second Value = %f",S_Value);
					printf("\n Total Value = %f",Total_Value);
								if(Total_Value!= 0){
									lcdClearScreen();
					sprintf(TString,"%g",Total_Value);			// Turn Answer variable into a String
					lcdWriteCommand(0xC0);						//Set to second line
					lcdWriteString(TString);
					lcdWriteCommand(0x02);
									F_Value = 0;
									S_Value = 0;
									Value = 0;
								}
					input3 = 0;
								input = 'G';
					break;
					case '*':						//clear Operation
					printf("\n Case = Clear Screen\n");	
					Reset_Calc();
					Limit_Reached = 1;
					break;
					case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:						//Number Entry
					
					printf("\n Case = input Operand = IN ||\n");	
					F_Value = Get_Value(0);
					printf("\n First Value = %f",F_Value);
					Value = 0;
//					if (input3 == 'A' ||input3 =='B' ||input3 == 'C' || input3 == 'D' 
//					|| input3 == '#' ||input3 == '*' ){
//						input3 = input2;
//						printf("\n First Value = %f",F_Value);
//					}
					input2 = input3;
					break;
}
}

