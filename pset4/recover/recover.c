#include <stdio.h>

int main(int argc, char *argv[])
// => argc = number of command line arguments
// => argv = list of command-line arguments
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover + name of a forensic image from which to recover JPEGs\n");
        return 1;
    }

    // remember filename
    char *infile = argv[1];

    // open input file
    FILE *raw_file = fopen(infile, "r");
    if (raw_file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // store 512 byte JPEG blocks into array
    const int BLOCK = 512;
    unsigned char buffer[BLOCK];
    // store number of found JPEGS
    int counter = 0;
    char filename[8]; // because "###.jpg\0" (?)
    // initialize file pointer
    FILE *image = NULL;


    // look for JPG
    // read in 512-byte-block, 1 byte each, into buffer
    while (fread(buffer, BLOCK, 1, raw_file) == 1)
    {
        // identify start of JPEG
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // if not the first JPEG, that is found - close "finished" JPEG
            if (counter > 0)
            {
                fclose(image);
            }

            // if true, name the new file
            sprintf(filename, "%03i.jpg", counter);

            // open the new image file
            image = fopen(filename, "w");
            if (image == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }
            // increment counter by 1
            counter++;
        }

        // segmentation fault occured without the if statement considering existance of raw_file => WHY?
        if (image != NULL)
        {
            // write to image file
            fwrite(buffer, BLOCK, 1, image);
        }
    }
    // close infile
    fclose(raw_file);

    // close outfile
    fclose(image);

    // success
    return 0;
}