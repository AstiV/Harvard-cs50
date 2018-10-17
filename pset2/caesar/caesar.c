#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
// => argc = number of command line arguments
// => argv = list of command-line arguments

{
    int key;
    string plaintext;

    // get the key from command line argument
    // argc must be 2 (./caesar and key)
    if (argc != 2)
    {
        printf("Please include your desired key to the command line argument!\n");
        return 1;
    }
    else if (argc == 2)
    {
        printf("The key you chose is: %s\n", argv[1]);
    }
    // argv[1] = key is of datatype string
    // convert key string to integer
    // use atoi function
    // check which value it will return if the string passed in doesn't contain all numbers
    key = atoi(argv[1]);

    // prompt for plaintext
    // output "plaintext: " (without a newline) and then
    // prompt the user for a string of plaintext (using get_string).
    plaintext = get_string("plaintext: ");

    // encipher
    // for each character in the plaintext string
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // check if character is alphabetic (isalpha)
        if (isalpha(plaintext[i]))
        {
            // preserve case - lower case characters
            if (islower(plaintext[i]))
            {
                // -97, as difference of ASCII value and alphabetical index (for lower case characters)
                // modulo 26 is used to wrap around the alphabet, e.g. x + 3 => a (26 = length of alphabet)
                // add 97 back again to access right ASCII value letter
                printf("%c", ((((plaintext[i] - 97) + key) % 26) + 97));
            }
            // preserve case - upper case characters
            else
            {
                printf("%c", ((((plaintext[i] - 65) + key) % 26) + 65));
            }
        }
        // preserve all other non-alphabetical characters
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}