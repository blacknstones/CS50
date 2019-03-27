/*example:
$ Height: 5
#
##
###
####
#####*/
#include <stdio.h>
#include <cs50.h> /*clang -o mario mario.c -lcs50*/
int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    for (int i = height; i > 0; i--)
    {
        for (int j = 0; j <= height - i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
