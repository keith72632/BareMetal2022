#ifndef LED_H_
#define LED_H_
#include <stdint.h>
#include "stm32f407xx.h"

#define INPUT          0x00
#define OUTPUT         0x01
#define ALT            0x02
#define ANALOG         0x03

#define NO_PULL        0x00
#define PULL_UP        0x01
#define PULL_DOWN      0x02

#define PIN_0          0
#define PIN_1          1
#define PIN_2          2
#define PIN_3          3
#define PIN_4          4
#define PIN_5          5
#define PIN_6          6
#define PIN_7          7
#define PIN_8          8
#define PIN_9          9
#define PIN_10         10
#define PIN_11         11
#define PIN_12         12
#define PIN_13         13
#define PIN_14         14
#define PIN_15         15

#define ATL_SPI_1      0x07
#define ATL_SPI_2      0x07
#define ALT_USART_1    0x07
#define ALT_USART_2    0x07
#define ALT_USART_3    0x07

typedef struct PinConf {
    uint8_t pin_no;
    uint8_t pin_mode;
    uint8_t pupd;
}PinConf_t;

typedef struct GPIO {
    PinConf_t pin;
    GPIO_RegDef_t *port;
} GPIO_t;

GPIO_t gpio_factory(GPIO_RegDef_t *port, uint8_t number, uint8_t mode, uint8_t pupd);
void gpio_pin_init(GPIO_t *pin);
void write_pin(GPIO_t *gpio);
void clear_pin(GPIO_t *gpio);
void reset_pin(GPIO_t *gpio);
uint32_t read_pin(GPIO_t *gpio);

#endif