# Questions

## What's `stdint.h`?

`stdint.h` is a header file in the C standard library.
It was introduced to allow programmers to write more portable code by providing a set of typedefs
that specify **exact-width integer types** and the defined minimum and maximum
allowable values for each type, using macros.

The naming convention for exact-width integer types is **intN_t** for signed int and **uintN_t** for unsigned int.

A **signed int** represents the "normal" size of data the processor deals with.
It is 4 bytes in size (or 32 bits). It can store integers in the range -32.767 ~ +32.767 portably.

An **unsigned int** is also 32 bits in size but it can only store integers in the 0 ~ +65.535 range.
**Unsigned** literally means that it can't store numbers with a sign, i.e. negative numbers, and instead can store twice as many
positive numbers.

For example `int8_t` and `uint64_t` amongst others could be declared together with defining their corresponding ranges
`INT8_MIN` to `INT8_MAX` and 0 (zero) to `UINT64_MAX`; using a similar but upper case naming convention.

In addition, stdint.h defines limits of integer types capable of holding object pointers such as `UINTPTR_MAX`,
the value of which depends on the processor and its address range.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

It makes sense to use aliases interchangeably for explicit fixed width integers.
Furthermore, it makes sense to specity the number of bytes of the integer because on one system an int might be a long in another.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
`BYTE`  = 8 bits         = 1 byte
`DWORD` = 32 bits        = 4 bytes
`LONG`  = signed 32 bits = 4 bytes
`WORD`  = 16 bits        = 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be?
## Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

ASCII       = BM
decimal     = 16973
hexadecimal = 0x424D

## What's the difference between `bfSize` and `biSize`?

`bfSize` = The size, in bytes, of the bitmap file
`biSize` = The number of bytes required by the structure (structure = the struct BITMAPINFOHEADER = fixed value).

## What does it mean if `biHeight` is negative?

If `biHeight` is **positive**, the bitmap is a bottom-up DIB (device-independent bitmap)
and its origin is the lower left corner.

If `biHeight` is **negative**, the bitmap is a top-down DIB (device-independent bitmap)
and its origin is the upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The `biBitCount` member of the `BITMAPINFOHEADER` structure determines the number of bits
that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

In case of an error, `fopen's` return value is `NULL`. In line 24 `fopen` returns `NULL` if it cannot find the file or if it doesn't exist.
In line 32 `fopen` returns `NULL` if the file cannot be written to.

## Why is the third argument to `fread` always `1` in our code?

It indicates how many elements of data to read. In this case, one pixel (byte) of data should be read per read.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

line 63: int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; // => sizeof(RGBTRIPLE) = 3 bytes (defined in bmp.h)
         int padding = (4 - (3 * 3) % 4) % 4;
         int padding = (4 - (9 % 4) % 4;
         int padding = (4 - 1) % 4;
         int padding = 3 % 4 = 3 // => (0 x 4) + 3 = 3 !

Line 63 makes sures that the number of bytes in every row is a multiple of 4.

## What does `fseek` do?

copy.c:
`fseek(inptr, padding, SEEK_CUR);`
CS50 reference:
`int fseek(FILE* fp, long int offset, int from_where);``
fp – file pointer
offset – Number of bytes/characters to be offset/moved from the current file pointer position
from_where – This is the current file pointer position from where offset is added.

`fseek` is used to change the offset of the file pointer `inptr`.
When reading a file, the pointer usually continues in one direction, from the start of the file to the end.

In this case, `fseek` checks for padding and has programm jump over it.

## What is `SEEK_CUR`?

`SEEK_CUR` (besides `SEEK_SET`and `SEEK_END`) is a constant to specify the file pointer position from where offset is added,
when using `fseek`.

With `SEEK_CUR`, the location of a pointer is changed from its current location.
