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
        printf("Only one argument!\nUsage: %s key\n", argv[0]);
        return 1;
    }

    // check if key is valid digit
    string k = argv[1];
    for (int i = 0; i < strlen(k); i++)
    {
        if (!isdigit(k[i])) // isdigit() == 0
        {
            printf("Only digit!\n");
            return 1;
        }
    }

    int key = atoi(k);
    string p = get_string("plaintext: ");
    printf("ciphertext: ");

    // Print the encoded string.
    for (int j = 0; j < strlen(p); j++)
    {

        // Ignore non-letter characters.
        if (!isalpha(p[j]))
        {
            printf("%c", p[j]);
            continue;
        }

        // Shift differently depending on case.
        int shift = islower(p[j]) ? 'a' : 'A';

        // Apply the cipher formula and print the result.
        int c = (p[j] - shift + key) % 26 + shift;
        printf("%c", c);
    }

    printf("\n");
    return 0;
}