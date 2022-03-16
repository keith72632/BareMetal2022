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

void adc_init(ADC_t *adc)
{
    ADC1_PCLK_EN();
    gpio_pin_init(&adc->input_pin);

    // Conversion sequence start
    adc->adc_addr->SQR3 |= ADC_CHANNEL_ONE;

    // Conversion sequence length
    adc->adc_addr->SQR1 |= ADC_SEQ_LEN_ONE;

    // Enable ADC module
    adc->adc_addr->CR2 |= CR2_ADON | SFTWR_START;
}

uint32_t adc_read(ADC_t *adc)
{
    while(!(adc->adc_addr->SR & EOC)){};

    return adc->adc_addr->DR;
}