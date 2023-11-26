#include "fonctions.h"
#include <time.h>

void sudoku_init (sudoku *sudoku)
{
    sudoku -> gameFinished = 0;
    sudoku -> time = time(NULL);
    sudoku->gameStarted = 1;
    sudoku->clickedPosX = -1;
	sudoku->clickedPosY = -1;
    sudoku->shiftHeld = 0;
    sudoku->posX = -1;
    sudoku->posY = -1;
    
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            sudoku->grid[x][y] = 0;
        }
    }
    shuffle(sudoku);
    solver(sudoku, 0, sudoku->grid);
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            sudoku -> gridValid[x][y] = sudoku ->grid[x][y];
        }
    }
    removeNumbers(sudoku, 80);
}