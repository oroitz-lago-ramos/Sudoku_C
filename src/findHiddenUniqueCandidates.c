#include <stdio.h>
#include <stdlib.h>

#include "fonctions.h"

int findHiddenUniqueCandidates(sudoku *sudoku)
{
    int ret = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku->gridClone[i][j] == 0)
            {
                for (int n = 0; n < 9; n++)
                {
                    int last = 0;
                    if (sudoku->megaGrid[i][j][n] == 1)
                    {
                        // Verif celib caché ligne:
                        for (int x = 0; x < 9; x++)
                        {
                            if (sudoku->megaGrid[x][j][n] == 1)
                            {
                                last++; // Last compte combien de fois un chiffre n est sur la ligne
                            }
                        }
                        if (last == 1) // Si il est seul ça veut dire qu'il est un celib caché
                        {
                            sudoku->gridClone[i][j] = n + 1;
                            ret++;
                        }
                        last = 0; // On remet a 0 la valeur de last pour proceder a la prochaine verif
                        // On refait en verifiant la colonne:
                        for (int x = 0; x < 9; x++)
                        {
                            if (sudoku->megaGrid[i][x][n] == 1)
                            {
                                last++;
                            }
                        }
                        if (last == 1)
                        {
                            sudoku->gridClone[i][j] = n + 1;
                            ret++;
                        }
                        last = 0;
                        // On verifie le mini-carré
                        int _i = 3 * (i / 3);
                        int _j = 3 * (j / 3);
                        for (int x = _i; x < _i + 3; x++)
                        {
                            for (int y = _j; y < _j + 3; y++)
                            {
                                if (sudoku->megaGrid[x][y][n] == 1)
                                {
                                    last++;
                                }
                            }
                        }
                        if (last == 1)
                        {
                            sudoku->gridClone[i][j] = n + 1;
                            ret++;
                        }
                    }
                }
            }
        }
    }
    return ret;
}