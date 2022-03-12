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
    GPIO_t out_D15 = pin_factory(GPIOD, PIN_15, OUTPUT, NO_PULL),
        in_A10 = pin_factory(GPIOB, PIN_10, INPUT, PULL_DOWN),
        btn = pin_factory(GPIOA, PIN_0, INPUT, PULL_DOWN);    

    pin_init(&out_D15);
    pin_init(&btn);
    pin_init(&in_A10);

    while(1)
    {
        if(read_pin(&btn) || read_pin(&in_A10)){
            write_pin(&out_D15);
        }
        clear_pin(&out_D15);
    }

    return 0;
}

