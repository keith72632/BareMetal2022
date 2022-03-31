#include "../includes/gpio.h"

GPIOx::GPIOx(GPIO_RegDef_t *_port, uint8_t no, uint8_t mode, uint8_t pullup)
{
	this->pin_no = no;
	this->pin_mode = mode;
	this->pupd = pullup;
	this->port = _port;

	if(port == GPIOA)
	{
		GPIOA_PCLK_EN();
	}
	else if(port == GPIOB)
	{
		GPIOB_PCLK_EN();
	}
	else if(_port == GPIOD)
	{
		GPIOD_PCLK_EN();
	}
	this->port->MODER |= (this->pin_mode << (2 * (this->pin_no)));
	this->port->PUPDR |= (this->pin_mode << (2 * (this->pin_no)));
}

void GPIOx::write()
{
	this->port->ODR |= (1 << this->pin_no);
}

uint32_t GPIOx::read()
{
	return this->port->IDR &= (ENABLE << this->pin_no);
}

void GPIOx::clear()
{
	this->port->ODR &= ~(ENABLE << this->pin_no);
}

void GPIOx::exti_interrupt()
{
	*NVIC_ISER0 |= (1 << 6); 
}

GPIO_t gpio_factory(GPIO_RegDef_t *port, uint8_t number, uint8_t mode, uint8_t pupd)
{
	GPIO_t temp = {
		.pin = {
			.pin_no = number,
			.pin_mode = mode,
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


// EXTIx corresponds to pin number. Ex. EXTI0 to pin 0, all ports

extern "C" {
	void EXTI0_IRQHandler(void)
	{
		
	}
}