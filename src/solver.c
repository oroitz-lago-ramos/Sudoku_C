
#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int solver(sudoku *sudoku, int count, int grid[9][9])
{
    Point p = findEmptyCell(grid);
    if (p.x == -1)
    {
        return count + 1;
    }

    for (int i = 0; i < 9; i++)
    {
        int checkNumber = testNumber(sudoku->grid, p, sudoku->range[i]);
        if (checkNumber == 1)
        {
            grid[p.x][p.y] = sudoku->range[i];
            if ((count = solver(sudoku, count, grid)) > 1)
            {
                return count;
            }
            grid[p.x][p.y] = 0;
        }
    }
    return count;
}