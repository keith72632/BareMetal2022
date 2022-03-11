#ifndef LED_H_
#define LED_H_
#include <stdint.h>
#include "stm32f407xx.h"

#define INPUT     0x00
#define OUTPUT    0x01

#define PULL_UP   0x01
#define PULL_DOWN 0x02

typedef struct PinConf {
    uint8_t pin_no;
    uint8_t pin_mode;
    uint8_t pupd;
}PinConf_t;

void led_init(GPIO_RegDef_t *port, PinConf_t pin);
void write_pin(GPIO_RegDef_t *port, PinConf_t pin);
void clear_pin(GPIO_RegDef_t *port, PinConf_t pin);
void reset_pin(GPIO_RegDef_t *port, PinConf_t pin);
uint32_t read_pin(GPIO_RegDef_t *port, PinConf_t pin);

#endif