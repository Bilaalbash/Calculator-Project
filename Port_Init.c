// 1. Pre-processor Directives Section
// Constant declarations to access port registers using 
// symbolic names instead of addresses
#include "Init.h"
//Port F //
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))



//Port D //
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

//Port E //
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

//Port A //
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

//Port B //
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// 2. Declarations Section
//   Function Prototypes
/*void PortD_Init(void);
void PortE_Init(void);
void PortA_Init(void);
void PortB_Init(void);
*/
//void delay(unsigned long halfsecs);

// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable

// Subroutine to initialize port D & E pins for input and output
// PORT D is output (columns)
// PORT E is input  (rows)
void PortD_init(void){ volatile unsigned long delay;
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

void PortE_init(void){ volatile unsigned long delay;
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

void PortA_init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000001;     // 1) A clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTA_CR_R |= 0x0C;           // allow changes to PA3-2       
  GPIO_PORTA_AMSEL_R &= 0x00;        // 3) disable analog function
  GPIO_PORTA_PCTL_R &= 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTA_DIR_R &= ~0x00;          // 5.1) no input, 
  GPIO_PORTA_DIR_R |= 0x0C;          // 5.2) PA3-2 output  
  GPIO_PORTA_AFSEL_R &= 0x00;        // 6) no alternate function
  GPIO_PORTA_PUR_R |= 0x00;          // disable pullup resistors on PA3-0       
  GPIO_PORTA_DEN_R |= 0x0C;          // 7) enable digital pins PA3-PA2     
}

void PortB_init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000002;     // 1) B clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTB_CR_R |= 0x3C;           // allow changes to PB5-2       
  GPIO_PORTB_AMSEL_R &= 0x00;        // 3) disable analog function
  GPIO_PORTB_PCTL_R &= 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTB_DIR_R &= ~0x00;          // 5.1) no input, 
  GPIO_PORTB_DIR_R |= 0x3C;          // 5.2) PB5-2 output  
  GPIO_PORTB_AFSEL_R &= 0x00;        // 6) no alternate function
  GPIO_PORTB_PUR_R |= 0x00;          // disable pullup resistors on PB5-PB2      
  GPIO_PORTB_DEN_R |= 0x3C;          // 7) enable digital pins PB5-PB2     3C
}

void PortF_init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}
