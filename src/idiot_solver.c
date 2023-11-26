#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int idiotSolver(sudoku *sudoku)
{
    int running = 1;
    while (running)
    {
        running = 0;
        findCandidates(sudoku);
        running += findUniqueCandidates(sudoku);
        running += findHiddenUniqueCandidates(sudoku);
        //running += findSegment(sudoku);
    }
    Point p = findEmptyCell(sudoku->gridClone);
    if (p.x == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}