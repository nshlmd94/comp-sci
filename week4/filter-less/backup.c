char type;
            if((i == 0 && j == 0) || (i == 0 && j == width-1) || (i == height-1 && j == 0) || (i == height-1 && j == width-1))
            {
                type = 'c'; // corner
            }
            else if((i == 0 && j > 0 && j < width-1) || (i == height-1 && j > 0 && j < width-1) || (j == 0 && i > 0 && i < height-1) || (j == width-1 && i > 0 && i < height-1))
            {
                type = 'e'; // edge
            }
            else
            {
                type = 'r';
            }
            
            if(type == 'r')
            {
                image[i][j].rgbtRed = (copy[i][j].rgbtRed + copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed) / 9;
                image[i][j].rgbtGreen = (copy[i][j].rgbtGreen + copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 9;
                image[i][j].rgbtBlue = (copy[i][j].rgbtBlue + copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 9;
            }
            else if(type == 'e')
            {
                
                

                
                image[i][j].rgbtRed = 
                image[i][j].rgbtGreen =
                image[i][j].rgbtBlue =
            }
            else if(type == 'c')
            {
                image[i][j].rgbtRed =
                image[i][j].rgbtGreen =
                image[i][j].rgbtBlue =
            }
            else
            {
                return;
            }