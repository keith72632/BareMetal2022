#include "uart.h"

USART_t usart_factory(USART_RegDef_t *uart_type)
{
    uint8_t rx_pin_no = 0, rx_pin_mode = 0, tx_pin_no = 0, tx_pin_mode = 0;
    GPIO_RegDef_t *temp;
    if(uart_type == USART3)
    {
        GPIOC_PCLK_EN();
        USART3_PCCK_EN();
        rx_pin_mode = ALT;
        rx_pin_no   = PIN_11;
        tx_pin_mode = ALT;
        tx_pin_no   = PIN_10;
        temp = GPIOC;
    }
    USART_t usart = {
        .type = uart_type,
        .rx_pin = gpio_factory(temp, rx_pin_no, rx_pin_mode, NO_PULL),
        .tx_pin = gpio_factory(temp, tx_pin_no, tx_pin_mode, NO_PULL)
    };

    usart.rx_pin.port->AFR[1] |= (7 << 12);
    usart.tx_pin.port->AFR[1] |= (7 << 8);

    return usart;
}

void uart_init(USART_t *uart)
{
    gpio_pin_init(&uart->rx_pin);
    gpio_pin_init(&uart->tx_pin);

    uart->type->CR1 |= (1 << 2) | (1 << 3) | (1 << 5);
    uart->type->BRR |= BAUD_9600;
    uart->type->CR1 |= (1 << 13);
}

void uart_put(USART_t *uart, const char c)
{
    while(!(uart->type->SR & TXE)){};

    uart->type->DR = c;
}