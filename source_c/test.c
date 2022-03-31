#include <stdio.h>

void NMI_Handler(void) __attribute__ ((weak, alias("Default_Handler")));

void Default_Handler()
{
    printf("Default\n");
}
int main()
{

    NMI_Handler();
    return 0;
}