#ifndef PLL_H
#define PLL_H

void SysTick_Init(void);
void PLL_Init(void);
void SysTick_Wait(unsigned long delay);
void SysTick_Wait_1us(unsigned long delay);
void SysTick_Wait_50ns(unsigned long delay);

#endif
