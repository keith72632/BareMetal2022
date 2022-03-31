#include "gpio.h"

GPIO_t gpio_factory(GPIO_RegDef_t *port, uint8_t number, uint8_t mode, uint8_t pupd)
{
	GPIO_t temp = {
		.pin = {
			.pin_mode = mode,
			.pin_no = number,
			.pupd = pupd
		},
		.port = port
	};

	return temp;
}
void gpio_pin_init(GPIO_t *pin)
{
	if(pin->port == GPIOA) GPIOA_PCLK_EN();
	if(pin->port == GPIOB) GPIOB_PCLK_EN();
	if(pin->port == GPIOC) GPIOC_PCLK_EN();
	if(pin->port == GPIOD) GPIOD_PCLK_EN();

	pin->port->MODER |= (pin->pin.pin_mode << (2 * pin->pin.pin_no));
	pin->port->PUPDR |= (pin->pin.pupd << (2 * pin->pin.pin_no));
}

void write_pin(GPIO_t *gpio)
{
	gpio->port->ODR |= (ENABLE << gpio->pin.pin_no);
}

void clear_pin(GPIO_t *gpio)
{
	gpio->port->ODR &= ~(ENABLE << gpio->pin.pin_no);
}

void reset_pin(GPIO_t *gpio)
{
	gpio->port->BSRR |= (ENABLE << gpio->pin.pin_no);
}

uint32_t read_pin(GPIO_t *gpio)
{
	return gpio->port->IDR &= (ENABLE << gpio->pin.pin_no); 
}