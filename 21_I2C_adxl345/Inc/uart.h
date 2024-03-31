

#include <stdint.h>
#include "stm32f4xx.h"

void uart2_tx_init(void);
char uart2_read(void);
void uart2_rxtx_init(void);
void uart2_rxtx_interrupt_init(void);
void dma1_stream6_init(uint32_src, uint32_dst, uint32_len);
#define SR_RXNE			(1U<<5)
#define HISR_TCIF6		(1U<<21)
#define HIFCR_CTCIF6	(1U<<21)
