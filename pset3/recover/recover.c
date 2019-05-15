#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char *argv[])
{
    // make sure the proper use
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./recover xxx.raw\n");
        return 1;
    }

    // create infile
    char *infile = argv[1];
    FILE *inptr  = fopen(infile, "r");

    // check if infile can be opened
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // create outfile
    FILE *img = NULL;

    // create buffer
    unsigned char buffer[512];
    char filename[8];

    // set the counter
    int counter = 0;


    // when reading the buffer
    while (fread(buffer, 512, 1, inptr))
    {
        // when new jpg header is found
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close previous JPEG outfile unless it's the first one
            if(counter > 0)
            {
                fclose(img);
            }

            // create and open new JPEG outfile
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter ++;


            // check is img is created
            if(img == NULL)
            {
                fclose(img);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }

        }

        // if the first jpg header is not found
        if (!counter)
        {
            continue;
        }

        fwrite(buffer, 512, 1, img);
    }

    fclose(inptr);
    fclose(img);
    printf("%i\n", counter);

    return 0;
}