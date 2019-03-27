#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollar;
    int counter = 0;
    int cents = round(dollar * 100);

    do
    {
        dollar = get_float("Input the amount of cash: ");
    } while (dollar <= 0);

    while (cents >= 25)
    {
        cents -= 25;
        counter++;
    }
    while (cents >= 10)
    {
        cents -= 10;
        counter++;
    }
    while (cents >= 5)
    {
        cents -= 5;
        counter++;
    }
    while (cents >= 1)
    {
        cents -= 1;
        counter++;
    }
    printf("The minimum number of coin needed: ");
}
