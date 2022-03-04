#include <stdio.h>

int add(int num1, int num2)
{
    return num1 + num2;
}

int main()
{
    int val;

    val = add(6, 7);

    printf("val = %d\n", val);
}