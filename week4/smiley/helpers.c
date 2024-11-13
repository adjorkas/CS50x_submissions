#include "helpers.h"

// Change all black pixels to a color of your choosing
void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop for height
    for (int i = 0; i < height; i++)
    {
        // Loop for width
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
            {
                image[i][j].rgbtRed = 0x3C;
                image[i][j].rgbtGreen = 0x32;
                image[i][j].rgbtBlue = 0x87;
            }
        }
    }
}