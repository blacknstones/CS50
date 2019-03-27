#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    long cNumber;
    // prompts until input is positive numeric number:
    do 
    {
        cNumber = get_long("Credit card number: ");
    }
    while (cNumber <= 0);
    
    // check the length of the card number:
    int count = 0;
    long valid = cNumber;
    while (valid > 0)
    {
        valid /= 10;
        count ++;
    }
    
    // check is card number length is valid:
    if (count < 13 || count > 16)
    {
        printf("INVALID\n");
    }
    
    // check every digit of the card number:
    int n1 = cNumber % 10;
    int n2 = (cNumber / 10) % 10;
    int n3 = (cNumber / 100) % 10;
    int n4 = (cNumber / 1000) % 10;
    int n5 = (cNumber / 10000) % 10;
    int n6 = (cNumber / 100000) % 10;
    int n7 = (cNumber / 1000000) % 10;
    int n8 = (cNumber / 10000000) % 10;
    int n9 = (cNumber / 100000000) % 10;    
    int n10 = (cNumber / 1000000000) % 10;
    int n11 = (cNumber / 10000000000) % 10;
    int n12 = (cNumber / 100000000000) % 10;
    int n13 = (cNumber / 1000000000000) % 10;
    int n14 = (cNumber / 10000000000000) % 10; 
    int n15 = (cNumber / 100000000000000) % 10;
    int n16 = (cNumber / 1000000000000000) % 10;
    
    // Luhn's Algorithm
    int c2 = (n2 * 2) / 10 + (n2 * 2) % 10;
    int c4 = (n4 * 2) / 10 + (n4 * 2) % 10;
    int c6 = (n6 * 2) / 10 + (n6 * 2) % 10;
    int c8 = (n8 * 2) / 10 + (n8 * 2) % 10;
    int c10 = (n10 * 2) / 10 + (n10 * 2) % 10;
    int c12 = (n12 * 2) / 10 + (n12 * 2) % 10;
    int c14 = (n14 * 2) / 10 + (n14 * 2) % 10;
    int c16 = (n16 * 2) / 10 + (n16 * 2) % 10;
    
    int check = (c2 + c4 + c6 +c8 + c10 + c12 + c14 + c16) 
              + (n1 + n3 + n5 + n7 + n9 + n11 + n13 + n15);
    
    // check if the card number is valid:
    if (check % 10 != 0)
    {
        printf("INVALID\n");
    }
    
    // check VISA: 13-dights, all starts with 4:
    else if (count == 13 && n13 == 4)
    {
        printf("VISA/n");
    }
  
    // check AMEX: 15-digits, all starts with 34 or 37:
    else if (count == 15)
    {
        if (n15 == 3 && (n14 == 3 || n14 == 7))
        {
            printf("AMEX\n");
        }
    }
    
    // check MASTERCARD: 16-digits, most starts with 51, 52, 53, 54, 55:
    // check VISA: 16-dights, all starts with 4:
    else if (count == 16)
    {
        if (n16 == 5 && (n15 == 1 || n15 == 2 || n15 == 3 || n15 == 4 || n15 == 5))
        {
            printf("MASTERCARD\n");
        }
        else if (n16 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
