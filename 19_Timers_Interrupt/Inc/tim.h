/*
 * tim.h
 *
 *  Created on: Oct 11, 2023
 *      Author: harnishpatel
 */

#ifndef TIM_H_
#define TIM_H_

void tim2_1hz_init(void);

#define SR_UIF		(1U<<0)
void tim2_1hz_interrupt_init(void);

#endif /* TIM_H_ */
