#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float value = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtRed = value;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float rgbtRed = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue);
            float rgbtGreen = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue);
            float rgbtBlue = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);
            
            if(rgbtRed > 255)
            {
                rgbtRed = 255;
            }

            if(rgbtGreen > 255)
            {
                rgbtGreen = 255;
            }

            if(rgbtGreen > 255)
            {
                rgbtGreen = 255;
            }

            image[i][j].rgbtBlue = rgbtBlue;
            image[i][j].rgbtGreen = rgbtGreen;
            image[i][j].rgbtRed = rgbtGreen;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int newWidth = width - 1 - j;

            image[i][j] = copy[i][newWidth];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumBlue = 0;
            int sumGreen = 0;
            int count = 0;

            for(int p = i-1; p < i+2; p++)
            {
                for(int q = j-1; q < j+2; q++)
                {
                    if(p < 0 || q < 0 || p > height-1 || q > width-1)
                    {
                        continue;
                    }

                    sumRed += copy[p][q].rgbtRed;
                    sumBlue += copy[p][q].rgbtBlue;
                    sumGreen += copy[p][q].rgbtGreen;
                    count++;
                }
            }

            image[i][j].rgbtRed = sumRed / count;
            image[i][j].rgbtBlue = sumBlue / count;
            image[i][j].rgbtGreen = sumGreen / count;
        }
    }

    return;
}
