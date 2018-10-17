from cs50 import get_int


def main():
    # promt user for valid input
    while True:
        print("Let's build a pyramid! Please let me know how high it should be!\nChoose a number from 1 to 23: ", end="")
        height = get_int()
        # print(height) # prints the input integer
        # "or" operator didn't work
        if height >= 0 and height <= 23:
            break

    # outer loop prints the rows (i = rows)
    for i in range(height):
        for space in range(height - i - 1):
            print(" ", end="")
        for pound in range(i + 1):
            print("#", end="")
        # prints the gap
        print("  ", end="")
        # prints second pyramid
        for pound2 in range(i + 1):
            print("#", end="")
        print("")


if __name__ == "__main__":
    main()
