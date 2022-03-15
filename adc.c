/*
There are many types of ADC, but essentially the boil down to two different kinds; read once or continuous read. The more
channels (bits), the higher the resolution. 
*/

#include "adc.h"

ADC_t adc_factory(ADC_RegDef_t *adc_base, GPIO_RegDef_t *gpio_port, uint8_t gpio_pin)
{
    ADC_t temp = {
        .adc_addr = adc_base,
        .input_pin = gpio_factory(gpio_port, gpio_pin, ANALOG, NO_PULL)
    };

    return temp;
}

void adc_init()
{
    ADC1_PCLK_EN();
}