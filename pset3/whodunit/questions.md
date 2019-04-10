 # Questions

## What's `stdint.h`?

It is a header file in the standard C library that defines a set of integer type aliases with specific width requirements.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To define different integer types with specific width. `uint8_t` is unsinged 8 bytes, `uint32_t` is unsigned 32 bits, `int32_t` is signed 32 bits, and `uint16_t` is unsigned 16 bits.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

A `BYTE` is 1 bytes, a `DWORD` is 4 bytes, a `LONG` is 4 bytes, and a `WORD` is 2 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

Contains the characters B and M, 0x4d42 in hexadecimal (reverse order), that identify the file type.

## What's the difference between `bfSize` and `biSize`?

biSize is the size of BITMAPINFOHEADER, which is 40 bytes.
bfSize is the file size in bytes of the full BMP (including both header and image itself).

## What does it mean if `biHeight` is negative?

If biHeight is positive, the bitmap is a bottom-up DIB (device-independent bitmap) 
  and its origin is the lower left corner.
	
If biHeight is negative, the bitmap is a top-down DIB (device-independent bitmap) 
  and its origin is the upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The biBitCount determines the number of bits that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in `copy.c`?

If the infile or outfile doesn't exist. 

## Why is the third argument to `fread` always `1` in our code?

It reads 1 byte of RGB triple at a time.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

 int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4
             = (4 - (3 * 3) % 4 ) % 4
             = 3

## What does `fseek` do?

Sets the file position of the stream to the given offset.

## What is `SEEK_CUR`?

This is the position from where offset is added, and `SEEK_CUR` is the current position of the file pointer.