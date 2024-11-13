#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = (int) round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            int newRed, newGreen, newBlue;

            newRed = (int) round((.393 * red + .769 * green + .189 * blue));
            newGreen = (int) round((.349 * red + .686 * green + .168 * blue));
            newBlue = (int) round((.272 * red + .534 * green + .131 * blue));

            if (newRed > 255)
            {
                newRed = 255;
            }

            if (newGreen > 255)
            {
                newGreen = 255;
            }

            if (newBlue > 255)
            {
                newBlue = 255;
            }

            image[i][j].rgbtRed = newRed;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtBlue = newBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tmp[i][j] = image[i][j];
            image[i][j] = image[i][width - 1 - j]; // "Why the -1?" The lesson here is: remember things are 0 indexed!
            image[i][width - 1 - j] = tmp[i][j]; // Array of size 10 => lastElement[9] => -1 ! Silly mistake, but figured it out! :D
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make an image copy to store old values
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int redSum, greenSum, blueSum, maxWidth, maxHeight;
    maxWidth = width - 1;
    maxHeight = height - 1;
    float count;

    // Loop through each pixel
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            redSum = greenSum = blueSum = count = 0;

            // Loop through each box around pixel
            for (int ly = -1; ly <= 1; ly++)
            {
                for (int lx = -1; lx <= 1; lx++)
                {
                    if (y + ly >= 0 && y + ly <= maxHeight && x + lx >= 0 && x + lx <= maxWidth)
                    {
                        // Sum pixel color values
                        redSum += copy[y + ly][x + lx].rgbtRed;
                        greenSum += copy[y + ly][x + lx].rgbtGreen;
                        blueSum += copy[y + ly][x + lx].rgbtBlue;
                        count++;
                    }
                }
            }

            // Set new pixel value
            image[y][x].rgbtRed = (int) round(redSum / count);
            image[y][x].rgbtGreen = (int) round(greenSum / count);
            image[y][x].rgbtBlue = (int) round(blueSum / count);
        }
    }

    return;
}