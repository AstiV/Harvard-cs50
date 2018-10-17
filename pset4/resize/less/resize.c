// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
// => argc = number of command line arguments
// => argv = list of command-line arguments

{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize n infile outfile\n");
        return 1;
    }

    // remember n and filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];


    // ensure that n is a positive integer less than or equal to 100
    if (n < 0 || n > 100)
    {
        fprintf(stderr, "Usage: n must be a positive integer less than or equal to 100\n");
        return 2;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf; // declaration reserves enough memory for a local variable to store that entire structure
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi; // declaration reserves enough memory for a local variable to store that entire structure
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // update bitmap header info for the outfile
    // declare new BITMAPFILEHEADER (new_bf) and new BITMAPINFOHEADER (new_bi)

    // 1. store changes in width and height
	BITMAPFILEHEADER new_bf;
	BITMAPINFOHEADER new_bi;
	new_bf = bf;
	new_bi = bi;
	new_bi.biWidth = bi.biWidth * n; // biWidth = width of image in pixels without padding!
	new_bi.biHeight = bi.biHeight * n; // biHeight = height of image in pixels
	printf("bi.biWidth was %i and new_bi.biWidth is %i. \n", bi.biWidth, new_bi.biWidth);
	printf("bi.biHeight was %i and new_bi.biHeight is %i. \n", bi.biHeight, new_bi.biHeight);

    // calculate further changes in header info

    // 2. calculate new padding to be able to calculate new biSizeImage (=> total image size in bytes, including pixels and padding!)
    int old_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // 3. claculate new biSizeImage as needed to calculate new bfSize
    // why use abs? => Height of a bmp image can be negative- if the image is stored top to bottom.
    // When calulaing the size of the image, negative doesn't work => absolute value of height needed!
    new_bi.biSizeImage = ((sizeof(RGBTRIPLE) * new_bi.biWidth) + new_padding) * abs(new_bi.biHeight);
    printf("bi.biSizeImage was %i and new_bi.biSizeImage is %i. \n", bi.biSizeImage, new_bi.biSizeImage);

    // 4. claculate new bfSize (=> total file size in bytes, including pixels, padding and headers!)
    new_bf.bfSize = new_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    printf("bf.bfSize was %i and new_bf.bfSize is %i. \n", bf.bfSize, new_bf.bfSize);

    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for infile's scanlines (not needed as padding is determined before header info already?)
    // int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {

        // write each row n times
        for (int m = 0; m < n; m++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over infile's padding, if any
            fseek(inptr, old_padding, SEEK_CUR);

            // write outfile's new padding
            for (int l = 0; l < new_padding; l++)
            {
                fputc(0x00, outptr);
            }

            // send cursor back to beginning of row to repeat the process n times
            fseek(inptr, -(bi.biWidth * 3 + old_padding ), SEEK_CUR);
        }

        // send cursor to the next row to repeat process
        fseek(inptr, bi.biWidth * 3 + old_padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
