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

	PinConf_t out15, in10, btn;
	out15.pin_no = 15;
	out15.pin_mode = OUTPUT;

    btn.pin_no = 0;
    btn.pin_mode = 0;
    btn.pupd = PULL_DOWN;

    in10.pin_no = 10;
    in10.pin_mode = INPUT;
    in10.pupd = PULL_DOWN;
    led_init(GPIOD, out15);
    led_init(GPIOA, btn);
    led_init(GPIOB, in10);

    while(1)
    {
        if(read_pin(GPIOA, btn) || read_pin(GPIOB, in10)){
            write_pin(GPIOD, out15);
        }
        clear_pin(GPIOD, out15);
    }

    return 0;
}

