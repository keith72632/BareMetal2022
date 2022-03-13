#include "gpio.h"
#include "uart.h"
#include "stm32f407xx.h"
#include <stdint.h>

#define LED_GREEN 12
#define LED_ORANGE 13
#define LED_RED 14
#define LED_BLUE 15


int main()
{
    GPIO_t out_D15 = gpio_factory(GPIOD, PIN_15, OUTPUT, NO_PULL),
        in_A10 = gpio_factory(GPIOB, PIN_10, INPUT, PULL_DOWN),
        btn = gpio_factory(GPIOA, PIN_0, INPUT, PULL_DOWN);

    USART_t usart3 = usart_factory(USART3);
    uart_init(&usart3);

    gpio_pin_init(&out_D15);
    gpio_pin_init(&btn);
    gpio_pin_init(&in_A10);

    while(1)
    {
        if(read_pin(&btn) || read_pin(&in_A10)){
            write_pin(&out_D15);
            uart_put(&usart3, 'X');
        }
        clear_pin(&out_D15);
    }

    return 0;
}

