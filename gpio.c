#include "gpio.h"

void led_init(GPIO_RegDef_t *port, PinConf_t pin)
{
	GPIOD_PCLK_EN();

	// uint32_t *pRccAhb1enr = (uint32_t*)0x40023830;


	// *pRccAhb1enr |= ( 1 << 3);
	//configure LED_GREEN
	port->MODER |= (pin.pin_mode << (2 * pin.pin_no));
}

void pin_out(GPIO_RegDef_t *port, PinConf_t pin)
{
	port->ODR |= (1 << pin.pin_no);
}