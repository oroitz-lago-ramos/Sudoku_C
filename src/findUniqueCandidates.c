#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int findUniqueCandidates(sudoku *sudoku)
{
    int ret = 0;
    int last;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int count = 0;
            if (sudoku->gridClone[i][j] == 0)
            {
                last = 0;
                for (int k = 0; k < 9; k++)
                {
                    if (sudoku->megaGrid[i][j][k] == 1)
                    {
                        last = k;
                        count++;
                    }
                }
            }
            if (count == 1)
            {
                ret++;
                sudoku->gridClone[i][j] = last + 1;
            }

        }
    }
    return ret;
}