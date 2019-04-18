#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
  // ensure proper usage
  if (argc != 4)
  {
    fprintf(stderr, "Usage: ./resize n infile outfile\n");
    return 1;
  }

  int n = atoi(argv[1]);
  if (n <= 0 || n > 100)
  {
    fprintf(stderr, "n, the resize factor, must be an integer satisfying 0 < n <= 100.\n");
    return 5;
  }

  // remember filenames
  char *infile = argv[2];
  char *outfile = argv[3];

  // open input file
  FILE *inptr = fopen(infile, "r");
  if (inptr == NULL)
  {
    fprintf(stderr, "Could not open %s.\n", infile);
    return 2;
  }

  // open output file
  FILE *outptr = fopen(outfile, "w");
  if (outptr == NULL)
  {
    fclose(inptr);
    fprintf(stderr, "Could not create %s.\n", outfile);
    return 3;
  }

  // read infile's BITMAPFILEHEADER
  BITMAPFILEHEADER bf, bfNew;
  fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
  bfNew = bf;

  // read infile's BITMAPINFOHEADER
  BITMAPINFOHEADER bi, biNew;
  fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
  biNew = bi;

  // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
  if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
      bi.biBitCount != 24 || bi.biCompression != 0)
  {
    fclose(outptr);
    fclose(inptr);
    fprintf(stderr, "Unsupported file format.\n");
    return 4;
  }

  // determine the new width and height
  biNew.biWidth = bi.biWidth * n;
  biNew.biHeight = bi.biHeight * n;

  // determine padding for scanlines
  int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
  int new_padding = (4 - (biNew.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

  // determine the new image size
  biNew.biSizeImage = (sizeof(RGBTRIPLE) * biNew.biWidth + new_padding) * abs(biNew.biHeight);
  bfNew.bfSize = biNew.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  // write new headers for outfile
  fwrite(&bfNew, sizeof(BITMAPFILEHEADER), 1, outptr);
  fwrite(&biNew, sizeof(BITMAPINFOHEADER), 1, outptr);

  // horizontal resize
  // iterate over infile's scanlines
  for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
  {
    // read and write everyline n times: vertical resize
    for (int j = 0; j < n; j++)
    {
      // iterate over pixels in scanline
      for (int k = 0; k < bi.biWidth; k++)
      {
        // temporary storage
        RGBTRIPLE triple;

        // read RGB triple from infile
        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

        // write RGB triple n times to outfile
        for (int l = 0; l < n; l++)
        {
          fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
      }

      // write new padding to outfile
      for (int m = 0; m < new_padding; m++)
      {
        fputc(0x00, outptr);
      }

      // skip over infile's padding, if any
      fseek(inptr, padding, SEEK_CUR);

      // go back to the beginning of the line of infile
      if (j < (n - 1))
      {
        fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE) + padding), SEEK_CUR);
      }
    }
  }
  // close infile
  fclose(inptr);

  // close outfile
  fclose(outptr);

  // success
  return 0;
}