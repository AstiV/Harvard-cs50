#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // promt user for input - do while loop?
    int cc_number;
    {
        printf("Please enter your Creditcard Number: ");
        cc_number = get_long_long();
    }

    // access last digit - cc_number % 10

    // multiply every other digit (start with second last digit, multiply every other digit by two)

    // sum those digits (14 => 1 + 4!)

    // add the sum to the sum of remaining digits

    // validate checksum (if last number is 0, number is valid)

    // validate company's identifier

    // validate number's length

    // print company that credit card belongs to

    // otherwise tell user that card is invalid

    return 0;
}