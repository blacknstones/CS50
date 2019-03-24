//Height: 8
//       #  #
//      ##  ##
//     ###  ###
//    ####  ####
//   #####  #####
//  ######  ######
// #######  #######
//########  ########

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    // iterate through every line
    for (int i = 0; i < height; i++)
    {
        //print space in every line
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}