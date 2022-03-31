/*
 * systick.h
 *
 *  Created on: Mar 19, 2022
 *      Author: khorton
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f407xx.h"
#include <stdint.h>

#define SYSTICK_ADDR       0xe000e010U

#define SYSTICK_LOAD_VALUE 16000U

#define CTRL_ENABLE        (1U << 0)
#define CTRL_CLKSRC        (1U << 2)
#define CTRL_CNTFLAG       (1U << 16)

#define SYSTICK        ((Systick_t*)SYSTICK_ADDR)

typedef struct Systick {
	uint32_t CTRL;
	uint32_t LOAD;
	uint32_t VAL;
	uint32_t CR;
}Systick_t;

namespace SysTick {
	void systick_delay_ms(uint32_t n);
}

#endif /* SYSTICK_H_ */
