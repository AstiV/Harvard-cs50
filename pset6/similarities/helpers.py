from nltk.tokenize import sent_tokenize

# how to use stringmethods (splitlines): https://docs.python.org/3/library/stdtypes.html#string-methods
# how to use datastructures (set and intersection): https://docs.python.org/3/tutorial/datastructures.html#sets


def lines(a, b):
    """Return lines in both a and b"""
    # take in string inputs a, b == file1, file2
    # split strings into lines (splitlines)
    # set == unordered collection with no duplicate elements
    # compare lines => use & or intersection()

    a = a.splitlines()
    b = b.splitlines()
    samelines = list(set(a) & set(b))

    return samelines


def sentences(a, b):
    """Return sentences in both a and b"""
    a = sent_tokenize(a)
    b = sent_tokenize(b)
    samesentences = list(set(a) & set(b))

    return samesentences


def allsubs(a, n):
    """Return all substrings of length n"""
    # declare temporal storage list for string slices
    tempstrings = []

    for i in range(len(a) - n + 1):
        # append saves stringslices in list "tempstrings"
        tempstrings.append(a[i:n + i])

    return tempstrings


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    # in python strings are arrays - so slicing is possible on strings!
    # https://www.pythoncentral.io/how-to-get-a-substring-from-a-string-in-python-slicing-strings/
    # https://developers.google.com/edu/python/strings
    # https://www.digitalocean.com/community/tutorials/how-to-index-and-slice-strings-in-python-3

    a = allsubs(a, n)
    b = allsubs(b, n)
    samesubstrings = list(set(a) & set(b))

    return samesubstrings
