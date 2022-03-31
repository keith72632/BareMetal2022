#include "../includes/uart.h"

USARTx::USARTx(USART_RegDef_t *type)
{
    uint8_t rx_pin_no, rx_pin_mode, tx_pin_no, tx_pin_mode, alt_mode, rx_alt_bit, tx_alt_bit;
	GPIO_RegDef_t *port;
	this->type = type;
    if(type == USART1)
    {

        GPIOA_PCLK_EN();
        USART1_PCCK_EN();
        rx_pin_mode = ALT;
        rx_pin_no   = PIN_10;
        tx_pin_mode = ALT;
        tx_pin_no   = PIN_9;
        alt_mode    = ALT_USART_1;
        port = GPIOA;
    }
    else if(type == USART2)
    {
        GPIOA_PCLK_EN();
        USART2_PCCK_EN();
        rx_pin_mode = ALT;
        rx_pin_no   = PIN_3;
        tx_pin_mode = ALT;
        tx_pin_no   = PIN_2;
        alt_mode    = ALT_USART_2;
        port = GPIOA;

    }
    else if(type == USART3)
    {
        GPIOC_PCLK_EN();
        USART3_PCCK_EN();
        rx_pin_mode = ALT;
        rx_pin_no   = PIN_11;
        tx_pin_mode = ALT;
        tx_pin_no   = PIN_10;
        tx_alt_bit = 8;
        rx_alt_bit = 12;
        alt_mode = ALT_USART_3;
        port = GPIOC;
    }
	GPIOx_t tx(port, tx_pin_no, tx_pin_mode, NO_PULL);
	GPIOx_t rx(port, rx_pin_no, rx_pin_mode, NO_PULL);

	port->AFR[1] |= (alt_mode << rx_alt_bit) | (alt_mode << tx_alt_bit);

	type->CR1 |= (1 << RE) | (1 << TE) | (1 << RXNEIE);
	type->BRR |= BAUD_9600;
	type->CR1 |= (1 << UE);
}

void USARTx::putc(const char c)
{
	while(!(this->type->SR & TXE)){};
	this->type->DR = c;
}

void USARTx::puts(const char *s)
{
    if(*s){
        this->putc(*s);
        this->puts(s+=1);
    }
    while(!(this->type->SR & TC)){};

}

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

void uart_put_byte(USART_t *uart, const uint8_t byte)
{
    while(!(uart->type->SR & TXE)){};

    uart->type->DR = byte;
}

void uart_puts(USART_t *uart, const char *s)
{
    if(*s){
        uart_putc(uart, *s);
        uart_puts(uart, s+=1);
    }
    while(!(uart->type->SR & TC)){};
}

void uart_putw(USART_t *uart, uint32_t word)
{
//	printf("word: %lx\n", word);
//	uint8_t firstByte, secondByte, thirdByte, fourthByte;
//	firstByte = word & 0xff000000;
//	secondByte = word & 0x00ff0000;
//	thirdByte = word & 0x0000ff00;
//	fourthByte = word & 0x000000ff;
//
////	uart_put_byte(uart, firstByte);
////	printf("first byte: %x\n", firstByte);
////	uart_put_byte(uart, secondByte);
////	printf("second byte: %x\n", secondByte);
////	uart_put_byte(uart, thirdByte);
////	printf("third byte: %x\n", thirdByte);
//	uart_put_byte(uart, fourthByte);
//	printf("fourth byte: %x\n", fourthByte);

}
uint8_t uart_getc(USART_t *uart){
    while(!(uart->type->SR & (1 << 5))){};

    return uart->type->DR;
}
