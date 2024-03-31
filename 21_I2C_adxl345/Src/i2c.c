#include "stm32f4xx.h"

#define GPIOBEN						(1U<<1)
#define I2C1EN						(1U<<21)

#define I2C_100KHz					80
#define SD_MODE_MAX_RISE_TIME		17
#define CR1_PE						(1U<<0)

#define SR2_BUSY					(1U<<1)
#define CR1_START					(1U<<8)
#define SR1_SB						(1U<<0)
#define SR1_ADDR					(1U<<1)
#define CR1_ACK						(1U<<10)
#define CR1_STOP					(1U<<9)
#define SR1_RXNE					(1U<<6)


//PinOut
//PB8------SCL
//PB9------SDA



void I2C1_init(void)
{
	/*Enable clock access to GPIOB*/
	RCC->AHB1ENR |= GPIOBEN;

	/*Set PB8 and PB9 mode to alternate function*/
	GPIOB->MODER &=~ (1U<<16);
	GPIOB->MODER |= (1U<<17);

	GPIOB->MODER &=~ (1U<<18);
	GPIOB->MODER |= (1U<<19);

	/*Set PB8 and PB9 output type to Open Drain*/
	GPIOB->OTYPER |= (1U<<8);
	GPIOB->OTYPER |= (1U<<9);


	/*Enable Pull-up for PB8 and PB9*/
	GPIOB->PUPDR |= (1U<<16);
	GPIOB->PUPDR &=~ (1U<<17);

	GPIOB->PUPDR |= (1U<<18);
	GPIOB->PUPDR &=~ (1U<<19);

	/*Enable clock access to I2C1*/
	RCC->APB1ENR |= I2C1EN;


	/*Enter Reset Mode*/
	I2C1->CR1 |= (1U<<15);

	/*Come out of Reset mode*/
	I2C1->CR1 &=~ (1U<<15);

	/*Set Peripheral Clock frequency*/
	I2C1->CR2 |= (1U<<4);  //16MHz

	/*Set I2C Standard mode, 100KHz*/
	I2C1->CCR |= I2C_100KHz;

	/*Set rise time*/
	I2C1->TRISE |= SD_MODE_MAX_RISE_TIME;

	/*Enable I2C1 Module*/
	I2C1->CR1 |= CR1_PE;

}

void I2C1_byteRead(char saddr, char maddr, char* data)
{
	volatile int tmp;

	/*Wait until its not busy*/
	while (I2C1->SR2 & (SR2_BUSY)){}

	/*Generate Start*/
	I2C1->CR1 |= CR1_START;

	/*Wait until start flag is set*/
	while (!(I2C1->SR1 & (SR1_SB))){}

	/*Transmit slave address + Write*/
	I2C1->DR = saddr << 1;

	/*Wait until Addr flag is set*/
	while (!(I2C1->SR1 &(SR1_ADDR))){}

	/*Clear addr flag*/
	tmp = I2C1->SR2;

	/*Send memory address*/
	I2C1->DR = maddr;

	/*Wait until transmitter empty*/
	while(!(I2C1->SR1 & SR1_TXE)){}

	/*Generate restart*/
	I2C1->CR1 |= CR1_START;

	/*Wait until start flag is set*/
	while (!(I2C1->SR1 & (SR1_SB))){}

	/*Transmit slave address + Read*/
	I2C1->DR = saddr << 1|1;

	/*Wait until Addr flag is set*/
	while (!(I2C1->SR1 &(SR1_ADDR))){}

	/*Disable the acknowledge*/
	I2C1->CR1 &=~ CR1_ACK;

	/*Clear addr flag*/
	tmp = I2C1->SR2;

	/*Generate stop after data received*/
	I2C1->CR1 |= CR1_STOP;

	/*Wait until RXNE flag is set*/
	while(!(I2C1->SR1 & SR1_RXNE)){}

	/*Read the data from DR*/
	*data++ = I2C1->DR;
}
















































