#include "stm32f4xx.h"


#define SYSTICK_LOAD_VAL		16000
#define CTRL_ENABLE				(1U<<0)
#define CTRL_CLKSOURCE			(1U<<2)
#define CTRL_COUNTFLAG			(1U<<16)





void systickDelayMs(int delay)
{
	/*Reload the value in register*/
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/*Clear the current value register*/
	SysTick->VAL = 0;

	/*Enable SysTick timer and select internal clock source*/
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSOURCE;

	for(int i; i<delay ; i++){
		/*Wait until CountFlag is SET*/
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0 ){}

	}
	SysTick->CTRL = 0;
}


