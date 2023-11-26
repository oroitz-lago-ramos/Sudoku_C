#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int findCandidates(sudoku *sudoku)
{
    int i;
    int j;
    int n;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {  
            if (sudoku->gridClone[i][j] == 0)
            {
                Point p;
                p.x = i;
                p.y = j;
                for (n = 1; n < 10; n++)
                {
                    sudoku->megaGrid[i][j][n - 1] = testNumber(sudoku->gridClone, p, n);
                }
            }
        }
    }
    return 0;
}
