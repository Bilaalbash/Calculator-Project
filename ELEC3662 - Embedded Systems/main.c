// ***** 1. Pre-processor Directives Section *****
#include <stdio.h>   // standard C library 
#include "UART.h"    // functions to implment input/output
#include "TExaS.h"   // Lab grader functions
#include "Keypad.h"

#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *)0x40007520))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))


// 2. Declarations Section

//   Function Prototypes
void PortD_Init(void);
void PortE_Init(void);
void delay(unsigned long halfsecs);
//void UART_Init();

// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable 
int main(void){
	UART_Init();
	PortD_Init(); // Init port PD0 PD1 PD2 PD3
	PortE_Init(); // Init port PE0 PE1 PE2 PE3
	Keypad_Init();
	printf("\nThis program tests the Keypad \n");

	
	while(1){
		
		readKeypad();
		delay(1);
		
	} 
}


// Subroutine to initialize port D & E pins for input and output
// PORT D is output (columns)
// PORT E is input  (rows)
void PortD_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000008;     // 1) D clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTD_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTD_CR_R |= 0x0F;           // allow changes to PD3-0       
  GPIO_PORTD_AMSEL_R &= 0x00;        // 3) disable analog function
  GPIO_PORTD_PCTL_R &= 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTD_DIR_R &= ~0x00;          // 5.1) no input, 
  GPIO_PORTD_DIR_R |= 0x0F;          // 5.2) PD3-0 output  
  GPIO_PORTD_AFSEL_R &= 0x00;        // 6) no alternate function
  GPIO_PORTD_PUR_R |= 0x00;          // disable pullup resistors on PD3-0       
  GPIO_PORTD_DEN_R |= 0x0F;          // 7) enable digital pins PF4-PF0     
}

void PortE_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000010;     // 1) E clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTE_CR_R |= 0x0F;           // allow changes to PE3-0       
  GPIO_PORTE_AMSEL_R &= 0x00;        // 3) disable analog function
  GPIO_PORTE_PCTL_R &= 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R &= ~0x0F;          // 5.1) PE3-0 input, 
  GPIO_PORTE_DIR_R |= 0x00;          // 5.2) no output  
  GPIO_PORTE_AFSEL_R &= 0x00;        // 6) no alternate function
  GPIO_PORTE_PUR_R |= 0x0F;          // enable pullup resistors on PE3-0       
  GPIO_PORTE_DEN_R |= 0x0F;          // 7) enable digital pins PE3-0     
}

void delay(unsigned long time){
  unsigned long i;
  while(time > 0){
    i = 6666665;
    while(i > 0){
      i = i - 1;
    }
    time = time - 1;
  }
}
