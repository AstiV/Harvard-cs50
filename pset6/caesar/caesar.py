from cs50 import get_string
import sys


def main():
    # => argv = list of command-line arguments
    # In C: argc = number of command line arguments
    # A python list knows its length, so do len(sys.argv)
    # to get the number of elements in argv.

    # get the key from command line argument
    # argc must be 2 (caesar.py and key)
    if len(sys.argv) != 2:
        print("Please include your desired key to the command line argument!\n")

    elif len(sys.argv) == 2:
        print(f"The key you chose is: {sys.argv[1]}")

    # argv[1] = key is of datatype string
    # convert key string to integer
    # use atoi function
    # check which value it will return if the string passed in doesn't contain all numbers
    key = int(sys.argv[1])

    # prompt for plaintext
    # output "plaintext: " (without a newline) and then
    # prompt the user for a string of plaintext (using get_string).
    plaintext = get_string("plaintext: ")

    # encipher
    # for each character in the plaintext string
    print("ciphertext: ", end="")

    # n = length of user input string
    n = len(plaintext)

    for i in range(n):
        # check if character is alphabetic (isalpha)
        # in python isalpha does not take any parameters
        # (in C isalpha(plaintext[i]))
        if (plaintext[i]).isalpha():

            # preserve case - lower case characters
            if (plaintext[i]).islower():

                # in python:
                # function ord() gets the int value of the char
                # to convert back afterwards, use function chr()

                # -97, as difference of ASCII value and alphabetical index (for lower case characters)
                # modulo 26 is used to wrap around the alphabet, e.g. x + 3 => a (26 = length of alphabet)
                # add 97 back again to access right ASCII value letter

                # store char value in variable as , end="" didn't work on calculation
                lowercasechar = chr(((((ord(plaintext[i]) - 97) + key) % 26) + 97))
                print(lowercasechar, end="")
            # preserve case - upper case characters
            else:
                uppercasechar = chr(((((ord(plaintext[i]) - 65) + key) % 26) + 65))
                print(uppercasechar, end="")

        # preserve all other non-alphabetical characters
        else:
            print(plaintext[i], end="")

    # print linebreak after string
    print()


if __name__ == "__main__":
    main()