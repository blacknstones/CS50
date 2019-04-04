#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int shift(char c);
int main(int argc, string argv[])
{
    // check if only one argument
    if (argc != 2)
    {
        printf("Only one argument!\n");
        return 1;
    }

    // check if keyword is valid alphabetic
    string keyword = argv[1];
    int z = strlen(keyword);
    int key[z]; // array with z elements
    for (int i = 0; i < z; i++)
    {
        if (!isalpha(keyword[i])) // isalpha == 0
        {
            printf("Only letter!\n");
            return 1;
        }
        else
        {
            key[i] = shift(keyword[i]);
            //printf("the key at index %i is %i\n", i, key[i]);
        }
    }

    //printf("the key has %i individual keys\n", z);
    string p = get_string("plaintext: ");
    printf("ciphertext: ");

    // set the first key
    int n = 0;

    // iterater the plaintext
    for (int j = 0; j < strlen(p); j++)
    {
        // skip non-letter characters
        if (!isalpha(p[j]))
        {
            printf("%c", p[j]);
            continue;
        }

        // set the key for individual letter
        int k = key[(n + z) % z];

        // shift differently depending on case
        int s = islower(p[j]) ? 'a' : 'A';

        // apply the key
        int cipher = (p[j] - s + k) % 26 + s;

        // un comment below to test
        // printf("%c will use key at %i, which is %i\n", p[j], (n + z) % z, k);
        printf("%c", cipher);
        n++;
    }

    printf("\n");
    return 0;
}

// the function of shifting character to
int shift(char c)
{
    int x = islower(c) ? 'a' : 'A';
    int y = (c - x) % 26;
    return y;
}