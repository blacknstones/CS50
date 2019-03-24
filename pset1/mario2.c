//Height: 5
//    #
//   ##
//  ###
// ####
//#####
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    //iterate through every line
    for (int i = 0; i < height; i++)
    {
        // print space in every line
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        // print hashes in every line
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}