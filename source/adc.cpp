/*
There are many types of ADC, but essentially the boil down to two different kinds; read once or continuous read. The more
channels (bits), the higher the resolution.
*/

#include "../includes/adc.h"

ADCx::ADCx(ADC_RegDef_t *adc_type)
{
	this->adc_type = adc_type;

	if(adc_type == ADC1)
	{
		ADC1_PCLK_EN();
	}

	adc_type->SQR3 |= ADC_CHANNEL_ONE;
	adc_type->SQR1 |= 0x00;
	adc_type->CR2 |= CR2_ADON;
}

void ADCx::start_conversion(void)
{
	this->adc_type->CR2 |= SFTWR_START;
}

void ADCx::start_continuous_conversion(void)
{
	this->adc_type->CR2 |= CONT;
	this->adc_type->CR2 |= SFTWR_START;
}

uint32_t ADCx::read(void)
{
	while(!(this->adc_type->SR & EOC)){}

	return this->adc_type->DR;
}
void _adc_init(void)
{
	RCC->AHB1ENR |= (1 << 0);

	GPIOA->MODER |= (1 << 2) | (1 << 3);

	RCC->APB2ENR |= (1 << 8);

	ADC1->SQR3 |= (1 << 0);

	ADC1->SQR1 |= 0x00;

	ADC1->CR2 |= (1 << 0);
}

void _start_conversion(void)
{
	ADC1->CR2 |= (1 << 30);
}

void _start_continuous_conversion(void)
{
	ADC1->CR2 |= (1 << 1);
	ADC1->CR2 |= (1 << 30);
}

uint32_t _adc_read()
{
	while(!(ADC1->SR & EOC)){}

	return ADC1->DR;
}
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
