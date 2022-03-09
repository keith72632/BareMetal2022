#ifndef LED_H_
#define LED_H_
#include <stdint.h>

#define _vo volatile

#define AHB1_OFFSET    0x0400U
#define AHB1_BASE      0x40020000U
#define GPIO_BASE      AHB1_BASE 
#define GPIOA_BASE     GPIO_BASE
#define GPIOB_BASE     (GPIOA_BASE + AHB1_OFFSET)       
#define GPIOC_BASE     (GPIOB_BASE + AHB1_OFFSET)       
#define GPIOD_BASE     (GPIOC_BASE + AHB1_OFFSET)       
#define GPIOE_BASE     (GPIOD_BASE + AHB1_OFFSET)       

typedef struct GPIO {
    _vo uint32_t mode;
    _vo uint32_t otype;
    _vo uint32_t ospeed;
    _vo uint32_t pupd;
    _vo uint32_t idr;
    _vo uint32_t odr;
    _vo uint32_t set_reset;
    _vo uint32_t lock_reg;
    _vo uint32_t alt[2];
}GPIO_Regs_t;


#define GPIOD          (GPIO_Regs_t*)GPIOD_BASE
void led_init();

#endif