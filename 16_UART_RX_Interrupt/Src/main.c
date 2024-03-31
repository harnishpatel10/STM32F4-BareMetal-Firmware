#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOAEN             (1U<<0) // Enable bit for GPIOA
#define GPIOA_5				(1U<<5)
#define LED_PIN				GPIOA_5


char key;

static void uart_callback(void);

int main(void)
{
	/*Enable the clock access*/
	RCC->AHB1ENR |=GPIOAEN;

	/*Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	uart2_rxtx_interrupt_init();
	while(1)
	{


	}
}
static void uart_callback(void)
{
	key = USART2->DR;
			if (key=='1')
					{
						GPIOA->ODR |= LED_PIN;
					}
					else
					{
						GPIOA->ODR &=~ LED_PIN;
					}
}

void USART2_IRQHandler(void)
{
	/*Check if RXNE is set*/
	if(USART2->SR & SR_RXNE)
	{
		uart_callback();

	}

}
