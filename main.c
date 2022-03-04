#include "led.h"
#include <stdint.h>

#define THING 1

int ret_int();

int main()
{
    const uint32_t x = 10;
    led_init();
    return ret_int();
}

int ret_int()
{
    return 66;
}