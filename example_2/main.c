#include <stdio.h>

int     sum(int a, int b);
int     minus(int a, int b);
int     mult(int a, int b);

int main()
{
    int a = sum(42, 42);
    printf("sum is %d\n", a);
    //------------------------
    int b = minus(42, 42);
    printf("minus is %d\n", b);
    //------------------------
    int c = mult(5, 5);
    printf("mult is %d\n", c);
}