/*
 * systick.c
 *
 *  Created on: Mar 19, 2022
 *      Author: khorton
 */


#include "systick.h"

void systick_delay_ms(int n)
{
	uint32_t *STCSR = (uint32_t *)(SYSTICK_ADDR);
	uint32_t *STRVR = (uint32_t *)(SYSTICK_ADDR + 0x04);
	uint32_t *STCVR = (uint32_t *)(SYSTICK_ADDR + 0x08);

	// configure systick

	// reload number of clock per millisecond
	SYSTICK->LOAD |= SYSTICK_LOAD_VALUE;
	// clear systick current value
	SYSTICK->VAL &= ~(0xffffffff);

	// enable systick and select internal clock
	SYSTICK->CTRL |= CTRL_ENABLE | CTRL_CLKSRC;

	for(int i = 0; i < n; i++){
		// wait until count flag is set
		while((SYSTICK->CTRL & CTRL_CNTFLAG) == 0){};
	}

	SYSTICK->CTRL &= ~(0xffffffff);
}
