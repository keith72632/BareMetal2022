#include "gpio.h"

void led_init(GPIO_RegDef_t *port, PinConf_t pin)
{
	if(port == GPIOA) GPIOA_PCLK_EN();
	if(port == GPIOB) GPIOB_PCLK_EN();
	if(port == GPIOC) GPIOC_PCLK_EN();
	if(port == GPIOD) GPIOD_PCLK_EN();

	port->MODER |= (pin.pin_mode << (2 * pin.pin_no));
	port->PUPDR |= (pin.pupd << (2 * pin.pin_no));
}

void write_pin(GPIO_RegDef_t *port, PinConf_t pin)
{
	port->ODR |= (1 << pin.pin_no);
}

void clear_pin(GPIO_RegDef_t *port, PinConf_t pin)
{
	port->ODR &= ~(1 << pin.pin_no);
}

void reset_pin(GPIO_RegDef_t *port, PinConf_t pin)
{
	port->BSRR |= (1 << pin.pin_no);
}

uint32_t read_pin(GPIO_RegDef_t *port, PinConf_t pin)
{
	return port->IDR &= (1 << pin.pin_no); 
}