#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

void shuffle(sudoku *sudoku)
{
    for (size_t i = 0; i < 9; i++)
    {
        sudoku->range[i] = i + 1;
    }
    
    int temporaryResult;
    for (int i = 0; i < 9; i++)
    {
        int n = rand()%9;
        temporaryResult = sudoku->range[i];
        sudoku->range[i] = sudoku->range[n];
        sudoku->range[n] = temporaryResult;

    }
}