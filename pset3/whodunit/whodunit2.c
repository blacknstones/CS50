// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

RGBTRIPLE new_triple(int bgr)
{
    RGBTRIPLE t;
    t.rgbtBlue  = (bgr >> 16)       ; // Shift right by 16 bits to remove green and red.
    t.rgbtGreen = (bgr >>  8) & 0xff; // Shift right by  8 bits to remove red, then AND with to remove blue.
    t.rgbtRed   = (bgr      ) & 0xff; // AND with 0xff to remove blue and green.
    return t;
}

// new_triple return a new triple created from bgr, which is
// a 24-bit number in the format 0xBBGGRR.
// 
// in other words, the first 8 bits of bgr contains the blue color,
// the second 8 bits the green color and the last (rightmost) bits
// contains the red color.
// 
// Only blue:  11111111 00000000 00000000 = ff0000
// Only green: 00000000 11111111 00000000 = 00ff00
// Only red:   00000000 00000000 11111111 = 0000ff
// 
// Then you can combine these to create new colors :D

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // filter out red
            if (triple.rgbtRed >= 0xfd)
            {
                // set background color
                triple = new_triple(0xffffff);
            }
            else
            {
                // set text color
                triple = new_triple(0xc1b6ff);
            }

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
