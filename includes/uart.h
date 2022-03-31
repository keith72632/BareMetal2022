#ifndef UART_H
#define UART_H
#include <stdint.h>
#include <stdio.h>
#include "stm32f407xx.h"

#define BAUD_9600    0x0683
#define RE           0x02
#define TE           0x03
#define RXNEIE       0x05
#define UE           0x0D
#define TXE          0x0080
#define TC           0x0040

typedef struct USARTx {
    USART_RegDef_t *type;
    USARTx(USART_RegDef_t *type);
    void putc(const char c);
    void puts(const char *s);
}USARTx_t;

typedef struct USART {
    USART_RegDef_t *type;
    GPIO_t rx_pin;
    GPIO_t tx_pin;
}USART_t;

USART_t usart_factory(USART_RegDef_t *uart_type);
void uart_init(USART_t *uart);
void uart_putc(USART_t *uart, const char c);
void uart_put_byte(USART_t *uart, const uint8_t byte);
void uart_putw(USART_t *uart, uint32_t word);
void uart_puts(USART_t *uart, const char *s);
uint8_t uart_getc(USART_t *uart);

#endif
