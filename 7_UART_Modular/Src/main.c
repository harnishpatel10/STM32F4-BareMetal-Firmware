#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"



int main(void)
{
	uar2_tx_init();
	while(1)
	{
		printf("RAM...RAM...RAM\n\r");
	}
}

