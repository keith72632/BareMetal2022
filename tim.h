/*
 * tim.h
 *
 *  Created on: Mar 22, 2022
 *      Author: khorton
 */

#ifndef TIM_H_
#define TIM_H_

#include "stm32f407xx.h"
#include <stdint.h>

#define TIM2_ADDR    0x40000000U
#define PRSCLR       (1600-1)
#define LOADVAL      (10000-1)
#define TIM2_CLK     (1 << 0)
#define CR1_CEN      (1 << 0)
#define UIF          (1 << 0)
#define TIM2_CLK_EN()(RCC->APB1ENR |= TIM2_CLK)

typedef struct TIM {
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMR1;
	uint32_t CCMR2;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
	uint32_t DCR;
	uint32_t DMAR;
	uint32_t TIM2_OR;
	uint32_t TIM5_OR;
}TIM_t;

#define TIM2    ((TIM_t*)TIM2_ADDR)

void tim2_1hz_init(void);

#endif /* TIM_H_ */
