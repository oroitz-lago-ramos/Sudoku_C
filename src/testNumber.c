#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int testNumber(int grid[9][9], Point p, int number)
{
    for (int i = 0; i < 9; i++)
    {
        if (grid[i][p.y] == number && i != p.x)
        {
            return 0;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if (grid[p.x][i] == number && i != p.y)
        {
            return 0;
        }
    }

    /* 
    int _i = 3 * (p.x / 3);
    int _j = 3 * (p.y / 3); 
    */
   
    for (int i = (p.x / 3) * 3; i < (p.x / 3) * 3 + 3; i++)
    {
        for (int j = (p.y / 3) * 3; j < (p.y / 3) * 3 + 3; j++)
        {

            if (grid[i][j] == number && (i != p.y && j != p.x))
            {
                return 0;
            }
        }
    }
    return 1;
}