#include "uart.h"

USART_t usart_factory(USART_RegDef_t *uart_type)
{
    uint8_t rx_pin_no, rx_pin_mode, tx_pin_no, tx_pin_mode, alt_mode;
    GPIO_RegDef_t *temp;
    if(uart_type == USART1)
    {
        GPIOA_PCLK_EN();
        USART1_PCCK_EN();
        rx_pin_mode = ALT;
        rx_pin_no   = PIN_10;
        tx_pin_mode = ALT;
        tx_pin_no   = PIN_9;
        temp        = GPIOA;
        alt_mode    = ALT_USART_1;
    }
    else if(uart_type == USART2)
    {
        GPIOA_PCLK_EN();
        USART2_PCCK_EN();
        rx_pin_mode = ALT;
        rx_pin_no   = PIN_3;
        tx_pin_mode = ALT;
        tx_pin_no   = PIN_2;
        temp        = GPIOA;
        alt_mode    = ALT_USART_2;

    }
    else if(uart_type == USART3)
    {
        GPIOC_PCLK_EN();
        USART3_PCCK_EN();
        rx_pin_mode = ALT;
        rx_pin_no   = PIN_11;
        tx_pin_mode = ALT;
        tx_pin_no   = PIN_10;
        temp        = GPIOC;
        alt_mode = ALT_USART_3;
    }
    USART_t usart = {
        .type = uart_type,
        .rx_pin = gpio_factory(temp, rx_pin_no, rx_pin_mode, NO_PULL),
        .tx_pin = gpio_factory(temp, tx_pin_no, tx_pin_mode, NO_PULL)
    };

    usart.rx_pin.port->AFR[1] |= (alt_mode << 12);
    usart.tx_pin.port->AFR[1] |= (alt_mode << 8);

    return usart;
}

void uart_init(USART_t *uart)
{
    gpio_pin_init(&uart->rx_pin);
    gpio_pin_init(&uart->tx_pin);

    uart->type->CR1 |= (1 << RE) | (1 << TE) | (1 << RXNEIE);
    uart->type->BRR |= BAUD_9600;
    uart->type->CR1 |= (1 << UE);
}

void uart_putc(USART_t *uart, const char c)
{
    while(!(uart->type->SR & TXE)){};

    uart->type->DR = c;
}

void uart_puts(USART_t *uart, const char *s)
{
    if(*s){
        uart_putc(uart, *s);
        uart_puts(uart, s+=1);
    }
    while(!(uart->type->SR & TC)){};
}

uint8_t uart_getc(USART_t *uart){
    if(uart->type->SR & 0x05)
    {
        return uart->type->DR;
    }
    else return 0;
}