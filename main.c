#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "stm32f407xx.h"
#include <stdint.h>
// #include <stdio.h>

#define LED_GREEN 12
#define LED_ORANGE 13
#define LED_RED 14
#define LED_BLUE 15

void delay(uint32_t factor)
{
    for(int i = 0; i < (factor * 1000); i++);
}
int main()
{
    const char header[] = "\n\rSTM32F407xx Drivers\n\r@Keith Horton\n\n\r";
    GPIO_t out_D15 = gpio_factory(GPIOD, PIN_15, OUTPUT, NO_PULL),
        in_A10 = gpio_factory(GPIOB, PIN_10, INPUT, PULL_DOWN),
        btn = gpio_factory(GPIOA, PIN_0, INPUT, PULL_DOWN);

    USART_t usart3 = usart_factory(USART3);

//    ADC_t adc1 = adc_factory(ADC1, GPIOA, PIN_1);
//    adc_init(&adc1);
    uart_init(&usart3);

    gpio_pin_init(&out_D15);
    gpio_pin_init(&btn);
    gpio_pin_init(&in_A10);

    uart_puts(&usart3, "Enter Password:");
    uart_puts(&usart3, header);
//    uint32_t input = adc_read(&adc1);

    _adc_init();
    _start_continuous_conversion();
    uint32_t input;
    while(1){
    	input = _adc_read();
//        if(read_pin(&btn) || read_pin(&in_A10)){
//            write_pin(&out_D15);
//            uart_puts(&usart3, "button pushed\n\r");
//            printf("input: %lx\n", input);
//            uart_putw(&usart3, input);
//            uart_put_byte(&usart3, 88);
//        }
//        clear_pin(&out_D15);
    	delay(1000);
    	// printf("reading = %ld mV\n", (input * 5));
    	uart_puts(&usart3, "ADC read\n\r");
    }

    return 0;
}
