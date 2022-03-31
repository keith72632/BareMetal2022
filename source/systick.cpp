/*
 * systick.c
 *
 *  Created on: Mar 19, 2022
 *      Author: khorton
 */


#include "../includes/systick.h"

void SysTick::systick_delay_ms(uint32_t n)
{
	// configure systick

	// reload number of clock per millisecond
	SYSTICK->LOAD |= SYSTICK_LOAD_VALUE;
	// clear systick current value
	SYSTICK->VAL &= ~(0xffffffff);

	// enable systick and select internal clock
	SYSTICK->CTRL |= CTRL_ENABLE | CTRL_CLKSRC;

	for(uint32_t i = 0; i < n; i++){
		// wait until count flag is set
		while((SYSTICK->CTRL & CTRL_CNTFLAG) == 0){};
	}

	SYSTICK->CTRL &= ~(0xffffffff);
}

