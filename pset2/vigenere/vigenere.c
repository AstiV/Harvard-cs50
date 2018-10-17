#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    string plaintext;
    //string ciphertext;

    // get the keyword from command line argument and promt user again, if it's not inserted
    // argc must be 2 (./vigenere and keyword)
    if (argc == 2)
    {
        printf("The key you chose is: %s\n", argv[1]);
    }
    else
    {
        printf("Please include your desired keyword to the command line argument!\n");
        return 1;
    }
    // keyword MUST be alphabetical
    // argv[1] = keyword is of datatype string
    // iterate through all characters of the keyword and check if they are alphabetical
    for (int j = 0, n = strlen(argv[1]); j < n; j++)
    {
        if (!isalpha(argv[1][j]))
        {
            printf("Please use an alphabetical keyword!\n");
            return 1;
        }
    }
    // prompt user for plaintext
    // output "plaintext: " (without a newline) and
    // prompt the user for a string of plaintext (using get_string).
    plaintext = get_string("plaintext: ");

    // encipher

    // store keyword and its length in variables
    string keyword = argv[1];
    int keyLength = strlen(keyword);

    // for each character in the plaintext string
    printf("ciphertext: ");
    for (int i = 0, j = 0, m = strlen(plaintext); i < m; i++)
    {
        // get the key for each letter - use only lowercase letters of keywords as shift is not case sensitive anyway
        // mod keyword index by keylength and subtract 97, as (for lower case letters) shift results from ASCII value - 97
        int keyLetter = tolower(keyword[j % keyLength]) - 97;

        // check if character of plaintext is alphabetic (isalpha) (verschachteltes if => "sowohl als auch")
        if (isalpha(plaintext[i]))
        {
            // preserve case - lower case characters
            if (islower(plaintext[i]))
            {
                // -97, as difference of ASCII value and alphabetical index (for lower case characters)
                // modulo 26 is used to wrap around the alphabet, e.g. x + 3 => a (26 = length of alphabet)
                // add 97 back again to access right ASCII value letter
                printf("%c", ((((plaintext[i] - 97) + keyLetter) % 26) + 97));
                // j = keyword index only increments when it's used (when character in plaintext is alphabetical)
                j++;
            }
            // preserve case - upper case characters
            else
            {
                printf("%c", ((((plaintext[i] - 65) + keyLetter) % 26) + 65));
                // j = keyword index only increments when it's used (when character in plaintext is alphabetical)
                j++;
            }
        }
        // preserve all other non-alphabetical characters
        else
        {
            printf("%c", plaintext[i]);
            // here, j is not incremented !!
        }
    }
    printf("\n");
}