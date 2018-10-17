#include <cs50.h>
#include <stdio.h>

int main(void)
{

    // promt user for input - do while loop
    int height;
    do
    {
        printf("Let's build a pyramid! Please let me know how high it should be!\nChoose a number from 1 to 23: ");
        height = get_int();
    }
    while (height < 0 || height > 23);
    // why is it smaller 0 and bigger 23 here??
    // --> because while reprompts user input again and again
    //until it is not smaller than 0 or bigger than 23!

    // draw pyramid - use for loops

    // this outer loop prints the rows (i = rows)
    for (int i = 0; i < height; i++)
    {
        // print spaces for left pyramid
        for (int space = (height - i) - 1; space > 0; space--)
        {
            printf(" ");
        }
        // print hashes for left pyramid
        for (int hash_left = 0; hash_left <= i; hash_left++)
        {
            printf("#");
        }
        // print gap
        for (int gap = 0; gap <= 0; gap++)
        {
            printf("  ");
        }

        // print hashes for right pyramid
        for (int hash_right = 0; hash_right <= i; hash_right++)
        {
            printf("#");
        }
        // print new line
        printf("\n");
    }
    return 0;
}
