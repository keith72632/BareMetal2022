#include "uart.h"

void uart_init(USART_RegDef_t *uart)
{

    uart->CR1 |= (1 << 2) | (1 << 3);
    uart->BRR |= BAUD_9600;
    uart->CR1 |= (1 << 13);
}