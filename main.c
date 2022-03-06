#include "led.h"
#include <stdint.h>

#define LED_GREEN 12
#define LED_ORANGE 13
#define LED_RED 14
#define LED_BLUE 15

// void start_rcc();
void led_init_all_main();
void led_on_main(uint8_t led_no);

uint32_t x = 5;
int main()
{
    x = 10;
    // start_rcc();
    led_init_all_main();

    led_on_main(LED_BLUE);

    return 0;
}

void led_init_all_main(void)
{

	uint32_t *pRccAhb1enr = (uint32_t*)0x40023830;
	uint32_t *pGpiodModeReg = (uint32_t*)0x40020C00;


	*pRccAhb1enr |= ( 1 << 3);
	//configure LED_GREEN
	*pGpiodModeReg |= ( 1 << (2 * LED_GREEN));
	*pGpiodModeReg |= ( 1 << (2 * LED_ORANGE));
	*pGpiodModeReg |= ( 1 << (2 * LED_RED));
	*pGpiodModeReg |= ( 1 << (2 * LED_BLUE));

}

void led_on_main(uint8_t led_no)
{
  uint32_t *pGpiodDataReg = (uint32_t*)0x40020C14;
  *pGpiodDataReg |= ( 1 << led_no);

}