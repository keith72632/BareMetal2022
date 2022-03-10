#ifndef LED_H_
#define LED_H_
#include <stdint.h>
#include "stm32f407xx.h"

#define OUTPUT    0x01

typedef struct PinConf {
    uint8_t pin_no;
    uint8_t pin_mode;
}PinConf_t;

void led_init(GPIO_RegDef_t *port, PinConf_t pin);
void pin_out(GPIO_RegDef_t *port, PinConf_t pin);

#endif