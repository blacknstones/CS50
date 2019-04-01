#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // check if only one argument
    if (argc != 2)
    {
        printf("Only one argument!\n");
        return 1;
    }

    // check if key is valid digit
    string k = argv[1];
    for (int i = 0; i < strlen(k); i++)
    {
        if (isdigit(k[i]) == 0)
        {
            printf("Only digit!\n");
            return 1;
        }
    }

    int key = atoi(k);
    string p = get_string("plaintext: ");
    printf("ciphertext: ");

    // iterate string
    for (int j = 0; j < strlen(p); j++)
    {
        if (islower(p[j])) //islower() != 0
        {
            printf("%c", ((p[j] - 97 + key) % 26 + 97)); // 97 is the ASCII value of 'a'
        }
        else if (isupper(p[j]))
        {
            printf("%c", ((p[j] - 65 + key) % 26 + 65)); // 65 is the ASCII value of 'A'
        }
        else
        {
            printf("%c", p[j]);
        }
    }
    printf("\n");
    return 0;
}