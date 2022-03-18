/*
 * adc.h
 *
 *  Created on: Mar 17, 2022
 *      Author: khorton
 */

#ifndef ADC_H_
#define ADC_H_


#include "stm32f407xx.h"

#define ADC_CHANNEL_ONE     (1U << 0)
#define ADC_SEQ_LEN_ONE     0x00
#define CR2_ADON            (1U << 0)
#define SFTWR_START         (1U << 30)
#define EOC                 (1U << 1)

typedef struct ADC_t {
    ADC_RegDef_t *adc_addr;
    GPIO_t input_pin;
}ADC_t;

void adc_init(ADC_t *adc);
ADC_t adc_factory(ADC_RegDef_t *adc_base, GPIO_RegDef_t *gpio_port, uint8_t gpio_pin);
uint32_t adc_read(ADC_t *adc);
void _adc_init(void);
void _start_conversion(void);
uint32_t _adc_read(void);
#endif /* ADC_H_ */
