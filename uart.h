#ifndef UART_H
#define UART_H
#include <stdint.h>
#include "stm32f407xx.h"

#define BAUD_9600    0x0683
#define TXE          0x0080
#define TC           0x0040

typedef struct USART {
    USART_RegDef_t *type;
    GPIO_t rx_pin;
    GPIO_t tx_pin;
}USART_t;

USART_t usart_factory(USART_RegDef_t *uart_type);
void uart_init(USART_t *uart);
void uart_put(USART_t *uart, const char c);

#endif