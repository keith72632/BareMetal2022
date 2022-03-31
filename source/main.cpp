#include "../includes/gpio.h"
#include "../includes/uart.h"
#include "../includes/tim.h"
#include "../includes/adc.h"
#include "../includes/uart.h"
#include "../includes/stm32f407xx.h"
#include"../includes/systick.h"
#include <stdint.h>

#define LED_GREEN 12
#define LED_ORANGE 13
#define LED_RED 14
#define LED_BLUE 15


int main()
{
	GPIOx_t out_D15(GPIOD, PIN_15, OUTPUT, NO_PULL),
        in_B10(GPIOB, PIN_10, INPUT, PULL_DOWN), 
        btn(GPIOA, PIN_0, INPUT, PULL_DOWN), 
        adc_pin(GPIOA, PIN_1, ANALOG, PULL_DOWN),
        int_pin(GPIOB, PIN_0, INPUT, PULL_DOWN);

    const char header[] = "\n\rSTM32F407xx Drivers\n\r@Keith Horton\n\n\r";

    USARTx_t usart3(USART3);

    ADCx_t adc1(ADC1);

    adc1.start_continuous_conversion();

    uint32_t input;

    int_pin.exti_interrupt();

    tim2_1hz_init();
    usart3.puts(header);
    while(1){
    	input = adc1.read();

        if(btn.read() || in_B10.read()){
            out_D15.write();

        }
        out_D15.clear();
    	SysTick::systick_delay_ms(1000);
        usart3.puts("tick\n\r");
    /* Uncomment for TIM2 delay
        tim2_1hz_init();
    */

    	usart3.puts("ADC read\n\r");
    }

    return 0;
}
