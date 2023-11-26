#include "fonctions.h"

int test_fin(sudoku *sudoku)
{
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            if (sudoku -> grid[x][y] != sudoku -> gridValid [x][y])
            {
                return 0;
            }
        }
    }
    return 1;
}