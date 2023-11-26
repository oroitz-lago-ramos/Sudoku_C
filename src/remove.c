#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int removeNumbers(sudoku *sudoku, int num ) 
{
    for (int i = 0; i < num; i++)
    {
        int x = rand() % 9;
        int y = rand() % 9;
        if (sudoku->grid[x][y] == 0)
        {
            i++;
            continue;
        }
        int temp = sudoku->grid[x][y];
        sudoku->grid[x][y] = 0;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                sudoku->gridClone[i][j] = sudoku->grid[i][j];
            }
        }
        if (!idiotSolver(sudoku))
            sudoku->grid[x][y] = temp;
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sudoku->gridClone[i][j] = sudoku->grid[i][j];
        }
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 9; k++)
            {
                sudoku->megaGrid[i][j][k] = 0;
            }
        }
    }
    return 0;
}

/* 
int removeNumbers(sudoku *sudoku, int num)
{
    int EMPTY_x;
    int EMPTY_y;

    for (int a = 0; a < num; a++)
    {
        EMPTY_x = rand() % 9;
        EMPTY_y = rand() % 9;

        if (sudoku->grid[EMPTY_x][EMPTY_y] == 0)
        {
            a--;
            continue;
        }
        int stock = sudoku->grid[EMPTY_x][EMPTY_y];
        sudoku->grid[EMPTY_x][EMPTY_y] = 0;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                sudoku->gridClone[i][j] = sudoku->grid[i][j];
            }
        }
        if (solver(sudoku, 0, sudoku->gridClone) > 1)
        {
            sudoku->grid[EMPTY_x][EMPTY_y] = stock;
        }
    }
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sudoku->gridClone[i][j] = sudoku->grid[i][j];
        }
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 9; k++)
            {
                sudoku->megaGrid[i][j][k] = 0;
            }
        }
    }
    return 0;
} 
 */