#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;

    // promt user for an amount of change
    do
    {
        printf("How much do I owe you? Enter the amount ($.¢¢): ");
        change = get_float();
    }
    while (change < 0 || change > 3.40282347e+38F); // number is maximum value for type float in C

    // convert dollars to cents
    change = change * 100;

    // round float to integer
    int newChange;

    newChange = round(change);
    // printf("%i\n", newChange);

    // always use largest coin possible
    // keep track of the coins used (how many coins returned? AND remaining change)
    //quarter = 25;
    //dime =    10;
    //nickel =   5;
    //penny =    1;
    int count =    0;

    while (newChange >= 25)
    {
        newChange = newChange - 25;
        count++;
    }

    while (newChange >= 10)
    {
        newChange = newChange - 10;
        count++;
    }

    while (newChange >= 5)
    {
        newChange = newChange - 5;
        count++;
    }

    while (newChange >= 1)
    {
        newChange = newChange - 1;
        count++;
    }

    printf("Number of coins used: %i\n", count);
}