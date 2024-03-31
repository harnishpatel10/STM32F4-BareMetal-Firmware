#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"



/*SETUP: Connect a jumper wire from PA6 to PA6*/
int timestamp = 0;
int main(void)
{

	tim2_pa5_output_compare();
	tim3_input_capture();

	while(1)
	{
		/*Wait until edge is captured*/
		while(!(TIM3->SR & SR_CC1IF)){}

		/*Read Captured counter value*/
		timestamp = TIM3->CCR1;
	}
}

