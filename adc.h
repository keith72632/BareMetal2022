#ifndef ADC_H
#define ADC_H

#include "stm32f407xx.h"

typedef struct ADC_t {
    ADC_RegDef_t *adc_addr;
    GPIO_t input_pin;
}ADC_t;

void adc_init(void);
ADC_t adc_factory(ADC_RegDef_t *adc_base, GPIO_RegDef_t *gpio_port, uint8_t gpio_pin);


#endif