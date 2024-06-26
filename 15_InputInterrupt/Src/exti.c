#include "exti.h"

#define GPIOCEN			(1U<<2)
#define SYSCFGEN		(1U<<14)


void pc13_exti_init(void)
{
	/*Disable Global Interrupt*/
	__disable_irq();
	/*Enable clock access to GPIOC*/
	RCC->AHB1ENR |= GPIOCEN;

	/*Enable clock access to SYSCFG*/
	RCC->APB2ENR |= SYSCFGEN;

	/*Set PC13 as Input pin*/
	GPIOC->MODER &=~ (1U<<26);
	GPIOC->MODER &=~ (1U<<27);

	/*Select PORTC for EXTI13*/
	SYSCFG->EXTICR[3] |= (1U<<5);

	/*Unmask EXTI13*/
	EXTI->IMR |= (1U<<13);

	/*Select falling edge trigger*/
	EXTI->FTSR |= (1U<<13);

	/*Enable EXTI13 in NVIC*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	/*Enable Global Interrupt*/
	__enable_irq();
}

