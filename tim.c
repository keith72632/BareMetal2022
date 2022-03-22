/*
 * tim.c
 *
 *  Created on: Mar 22, 2022
 *      Author: khorton
 */


#include "tim.h"


void tim2_1hz_init()
{
	// Enable the clock
	TIM2_CLK_EN();
	//Set the prescaler value
	TIM2->PSC = PRSCLR;
	//Set auto-reload value
	TIM2->ARR = LOADVAL;
	//Clear counter
	TIM2->CNT &= ~(0xffffffff);
	//Enable timer
	TIM2->CR1 |= CR1_CEN;

	//wait for uif
	while(!(TIM2->SR & UIF)){};

	//clear uif
	TIM2->SR &= ~(0xffffffff);
}
