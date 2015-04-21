#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember resize factor and convert to an int
    int n = atoi(argv[1]);
    
    // check resize factor is within required range
    if (n < 1 || n > 100)
    {
        printf("Resize factor must be between 1 and 100!\n");
        return 2;
    }  
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file, error if not possible
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file, error if not possible
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0, error if not
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    // initialise outfile's BITMAPFILEHEADER & BITMAPINFOHEADER
    BITMAPFILEHEADER bf_out = bf;
    BITMAPINFOHEADER bi_out = bi;

    // determine outfile's biWidth & biHeight
    bi_out.biWidth = bi.biWidth * n;
    bi_out.biHeight = bi.biHeight * n;
    
     // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_out = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine outfile's biSizeImage
    bi_out.biSizeImage = (((bi_out.biWidth * sizeof(RGBTRIPLE)) + padding_out) * abs(bi_out.biHeight));
    
    // determine outfile's bfSize
    bf_out.bfSize = bi_out.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    // temporary storage
    RGBTRIPLE triple;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {   
        //loop through to repeat scanlines by n
        for (int r = 0; r < n; r++)
        {  
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {  
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for(int t = 0; t < n; t++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            } 

            // add in padding for outfile (if necessary)
            for (int k = 0; k < padding_out; k++)
            {
                fputc(0x00, outptr);
            }
            
            // return pointer to beginning of line
            fseek(inptr, - (bi.biWidth * sizeof(RGBTRIPLE)),SEEK_CUR);
        }
        
        // change to next scanline
        fseek(inptr, (bi.biWidth * sizeof(RGBTRIPLE)) + padding, SEEK_CUR); 
            
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
   

    // that's all folks
    return 0;
}
