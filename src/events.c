#include "fonctions.h"
#include <stdlib.h>
#include <stdio.h>

void eventListener(sudoku *sudoku, int *isOpen)
{
    SDL_Event events;
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_MOUSEMOTION:
            sudoku->posX = events.motion.x / CELL_SIZE;
            sudoku->posY = events.motion.y / CELL_SIZE;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (events.button.button == SDL_BUTTON_LEFT)
            {
                if (sudoku->clickedPosX == sudoku->posX && sudoku->clickedPosY == sudoku->posY)
                {
                    sudoku->clickedPosX = -1;
                    sudoku->clickedPosY = -1;
                }
                else
                {
                    sudoku->clickedPosX = sudoku->posX;
                    sudoku->clickedPosY = sudoku->posY;
                }
            }

            break;

        case SDL_KEYDOWN:
            if (events.key.keysym.sym >= SDLK_1 && events.key.keysym.sym <= SDLK_9 && (sudoku->clickedPosX != -1) && (sudoku->gameStarted))
            {
                if (sudoku->gridClone[sudoku->clickedPosY][sudoku->clickedPosX] == 0)
                {
                    if (sudoku->shiftHeld)
                    {
                        if (sudoku->megaGrid[sudoku->clickedPosY][sudoku->clickedPosX][events.key.keysym.sym - SDLK_0 - 1] == 0)
                        {
                            sudoku->megaGrid[sudoku->clickedPosY][sudoku->clickedPosX][events.key.keysym.sym - SDLK_0 - 1] = events.key.keysym.sym - SDLK_0;
                        }
                        else
                        {
                            sudoku->megaGrid[sudoku->clickedPosY][sudoku->clickedPosX][events.key.keysym.sym - SDLK_0 - 1] = 0;
                        }
                    }
                    else
                    {
                        sudoku->grid[sudoku->clickedPosY][sudoku->clickedPosX] = events.key.keysym.sym - SDLK_0;
                    }
                }
            }

            else if (events.key.keysym.sym == SDLK_BACKSPACE)
            {
                if (sudoku->shiftHeld == 0)
                {
                    if (sudoku->grid[sudoku->clickedPosY][sudoku->clickedPosX] == 0)
                    {
                        for (int k = 0; k < 9; k++)
                        {
                            sudoku->megaGrid[sudoku->clickedPosY][sudoku->clickedPosX][k] = 0;
                        }
                    }
                    else if (sudoku->gridClone[sudoku->clickedPosY][sudoku->clickedPosX] == 0)
                    {
                        sudoku->grid[sudoku->clickedPosY][sudoku->clickedPosX] = 0;
                    }
                }
                else
                {
                    for (int i = 0; i < 9; i++)
                    {
                        for (int j = 0; j < 9; j++)
                        {
                            if (sudoku->gridClone[i][j] == 0)
                            {
                                sudoku->grid[i][j] = 0;
                                for (int k = 0; k < 9; k++)
                                {
                                    sudoku->megaGrid[i][j][k] = 0;
                                }
                            }
                        }
                    }
                }
            }

            else if (events.key.keysym.sym == SDLK_SPACE)
            {
                sudoku_init(sudoku);
            }

            else if (events.key.keysym.sym == SDLK_LSHIFT)
            {
                sudoku->shiftHeld = 1;
            }

            else if (events.key.keysym.sym == SDLK_ESCAPE)
            {
                *isOpen = 0;
                break;
            }

            break;
        case SDL_KEYUP:
            if (events.key.keysym.sym == SDLK_LSHIFT)
            {
                sudoku->shiftHeld = 0;
            }
            break;

        case SDL_QUIT:
            *isOpen = 0;
            break;
        }
    }
}

/* 
int test()
{
    int tab[9][9];

    tab[0][0] |= (1 << 8);
    tab[0][0] |= (1 << 7);

    tab[0][0] ^= (1 << 8);

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; i < 9; j++)
        {
            if (tab[i][j] & (1 << (i - 1)))
            {
                // DESSINER LE CANDIDAT LOL
            }
        }
    }
} 
*/