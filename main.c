#include "gpio.h"
#include "stm32f407xx.h"
#include <stdint.h>

#define LED_GREEN 12
#define LED_ORANGE 13
#define LED_RED 14
#define LED_BLUE 15


uint32_t x = 5;
int main()
{
    x = 10;

	PinConf_t pin_15;
	pin_15.pin_no = 15;
	pin_15.pin_mode = OUTPUT;

    led_init(GPIOD, pin_15);

    pin_out(GPIOD, pin_15);

    return 0;
}

