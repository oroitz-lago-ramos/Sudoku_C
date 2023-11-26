#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

void printSudoku(sudoku *sudoku)
{
    printf("-------------------------\n");
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0 && i != 0)
        {
            printf("|-------|-------|-------|\n");
        }
        for (int j = 0; j < 9; j++)
        {
            if (j % 3 == 0){
                printf("| ");
            }
            printf("%d ", sudoku->grid[i][j]);
        }
        printf("|\n");
    }
    printf("-------------------------\n");
}