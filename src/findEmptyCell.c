#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

Point findEmptyCell(int grid[9][9])
{
    Point p;
    p.x = -1;
    p.y = -1;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (grid[i][j] == 0)
            {
                p.x = i;
                p.y = j;
                return p;
            }
        }
    }
    return p;
}