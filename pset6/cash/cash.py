from cs50 import get_float


def main():
    # promt user for an amount of change
    while True:
        print("How much do I owe you? Enter the amount ($.¢¢): ", end="")
        change = get_float()
        if change > 0:
            break
    # input is a value in Dollars
    # convert $ into ¢ ($1 = ¢100)
    change = change * 100
    # round function also exists in python (which library?)
    # round float to integer

    intChange = round(change)

    # always use largest coin possible
    # keep track of the coins used (how many coins returned? AND remaining change)
    # quarter = 25;
    # dime =    10;
    # nickel =   5;
    # penny =    1;

    # initialize coin counter
    count = 0
    # use modulo => returns the remainder of the division
    # 50 % 5 == 0
    # 50 % 10 == 0
    # 50 % 49 == 1
    # 53 % 50 == 3
    # x // y for integer division
    # x / y for float divison

    if (intChange >= 25):
        count += intChange // 25
        intChange %= 25
    if (intChange >= 10):
        count += intChange // 10
        intChange %= 10
    if (intChange >= 5):
        count += intChange // 5
        intChange %= 5
    if (intChange >= 1):
        count += intChange

    print(count)


if __name__ == "__main__":
    main()