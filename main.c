#include "led.h"
#include <stdint.h>

#define LED_GREEN 12
#define LED_ORANGE 13
#define LED_RED 14
#define LED_BLUE 15

// void start_rcc();
void led_init_all_main(GPIO_Regs_t *port, uint8_t pinNo);
void led_on_main(GPIO_Regs_t *port, uint8_t led_no);

uint32_t x = 5;
int main()
{
    x = 10;
    // start_rcc();
	// GPIO_Regs_t *pGpiodModeReg = (GPIO_Regs_t*)GPIOD_BASE;

    led_init_all_main(GPIOD, LED_GREEN);

    led_on_main(GPIOD, LED_GREEN);

    return 0;
}

void led_init_all_main(GPIO_Regs_t *port, uint8_t pinNo)
{

	uint32_t *pRccAhb1enr = (uint32_t*)0x40023830;


	*pRccAhb1enr |= ( 1 << 3);
	//configure LED_GREEN
	port->mode |= (1 << (2 * pinNo));
}

void led_on_main(GPIO_Regs_t *port, uint8_t led_no)
{
	port->odr |= (1 << led_no);
}