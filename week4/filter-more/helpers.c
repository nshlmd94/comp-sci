#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float value = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = value;
            image[i][j].rgbtRed = value;
            image[i][j].rgbtGreen = value;
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
            image[i][j] = copy[i][width-1-j];
        }
    }
    return;
}

// Blur image via Box Blur
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
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            int count = 0;

            for(int n = i-1; n < i+2; n++)
            {
                for(int m = j-1; m < j+2; m++)
                {
                    if(n < 0 || m < 0 || n > height-1 || m > width-1)
                    {
                        continue;
                    }

                    redSum += copy[n][m].rgbtRed;
                    greenSum += copy[n][m].rgbtGreen;
                    blueSum += copy[n][m].rgbtBlue;
                    count++;
                }
            }

            image[i][j].rgbtRed = redSum / count;
            image[i][j].rgbtBlue = blueSum / count;
            image[i][j].rgbtGreen = greenSum / count;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            //int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            //int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
            int gx1D[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
            int gy1D[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
            int gxRed = 0;
            int gxGreen = 0;
            int gxBlue = 0;
            int gyRed = 0;
            int gyGreen = 0;
            int gyBlue = 0;
            int count = 0;

            for(int n = i-1; n < i+2; n++)
            {
                for(int m = j-1; m < j+2; m++)
                {
                    if(n < 0 || m < 0 || n > height-1 || m > width-1)
                    {
                        count++;
                        continue;
                    }

                    gxRed += copy[n][m].rgbtRed * gx1D[count];
                    gyRed += copy[n][m].rgbtRed * gy1D[count];

                    gxBlue += copy[n][m].rgbtBlue * gx1D[count];
                    gyBlue += copy[n][m].rgbtBlue * gy1D[count];

                    gxGreen += copy[n][m].rgbtGreen * gx1D[count];
                    gyGreen += copy[n][m].rgbtGreen * gy1D[count];

                    count++;
                }
            }

            if(sqrt(pow(gxRed, 2) + pow(gyRed, 2)) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sqrt(pow(gxRed, 2) + pow(gyRed, 2));
            }

            if(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sqrt(pow(gxBlue, 2) + pow(gyBlue, 2));
            }

            if(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sqrt(pow(gxGreen, 2) + pow(gyGreen, 2));
            }
        }
    }
    return;
}
