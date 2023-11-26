#include "fonctions.h"
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
/*
void *reallocTable(void *ptr, size_t len, size_t elemSize, size_t originalSize, void *newElem)
{
    size_t size = len * elemSize;
    if (size + elemSize >= originalSize)
    {
        void *newTable = malloc(size * 2);

        memcpy(newTable, ptr, size);
        memcpy(newTable + size, newElem, elemSize);
        free(ptr);
        return newTable;
    }
    memcpy(ptr + size, newElem, elemSize);
    return ptr;
}
*/

int main(int ac, char **av)
{
    srand(time(NULL));
    if (ac < 2)
    {
        printf("Usage: %s <file>\n", av[0]);
        return 1;
    }
    FILE *file = fopen(av[1], "r");
    if (!file)
    {
        printf("Error: could not open file %s\n", av[1]);
        return 1;
    }

    char line[50];

    sudoku sudoku;

    int n = 0;

    while (fgets(line, 50, file))
    {
        char **characters = strsplit(line, ' ');

        for (int i = 0; i < 9; i++)
        {
            sudoku.grid[n][i] = atoi(characters[i]);
            free(characters[i]);
        }
        free(characters);
        n++;
    }
    /* printf("Grille de depart:\n");
    printSudoku(&sudoku);
    shuffle(&sudoku);
    solver(&sudoku);
     if (res)
    {
        printf("Il a trouve une solution!\n");
        printf("Sudoku resolu avec shuffle :\n");
        printSudoku(&sudoku);
    }
    else {printf("Il a pas trouve solutions");} */

    // removeNumbers(&sudoku);

    // printf("Resolu ca bg: \n");
    // printSudoku(&sudoku);
    sudoku.gameStarted = 0;

    initGraphics(&sudoku);
    
	
    int isOpen = 1;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 9; k++)
            {
                sudoku.megaGrid[i][j][k] = 0;
            }
        }
    }

    while (isOpen)
    {
        eventListener(&sudoku, &isOpen);
        SDL_Rect src = {0, 0, GRID_SIZE, GRID_SIZE};

        SDL_SetRenderDrawColor(sudoku.renderer, 255, 255, 255, 255);
        SDL_RenderClear(sudoku.renderer);
        SDL_RenderCopy(sudoku.renderer, sudoku.gridTexture, &src, &src);
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                // Carrés de selection ( border a pos xy et fill clickedxy)
                SDL_Rect selectionRectangle = {j * CELL_SIZE + 1, i * CELL_SIZE + 1, CELL_SIZE - 1, CELL_SIZE - 1};
                if (sudoku.clickedPosX != -1 && sudoku.clickedPosY != -1 && sudoku.megaGrid[i][j][sudoku.grid[sudoku.clickedPosY][sudoku.clickedPosX] - 1] && sudoku.clickedPosX != -1)
                {
                    SDL_SetRenderDrawColor(sudoku.renderer, 0, 255, 255, 255);
                    SDL_RenderFillRect(sudoku.renderer, &selectionRectangle);
                    SDL_SetRenderDrawColor(sudoku.renderer, 255, 255, 255, 255);
                }
                if (sudoku.clickedPosX != -1 && sudoku.grid[sudoku.clickedPosY][sudoku.clickedPosX] != 0 && sudoku.grid[i][j] == sudoku.grid[sudoku.clickedPosY][sudoku.clickedPosX])
                {

                    SDL_SetRenderDrawColor(sudoku.renderer, 0, 255, 255, 255);
                    SDL_RenderFillRect(sudoku.renderer, &selectionRectangle);
                    SDL_SetRenderDrawColor(sudoku.renderer, 255, 255, 255, 255);
                }
                if (i == sudoku.clickedPosY && j == sudoku.clickedPosX && (sudoku.clickedPosX != -1))
                {
                    SDL_RenderFillRect(sudoku.renderer, &selectionRectangle);
                }

                if (i == sudoku.posY && j == sudoku.posX)
                {
                    SDL_RenderDrawRect(sudoku.renderer, &selectionRectangle);
                }

                // Ecriture des chiffres
                SDL_Rect rectangle = {j * CELL_SIZE + CELL_MARGIN, i * CELL_SIZE + CELL_MARGIN, FONT_SIZE, FONT_SIZE};

                if (sudoku.grid[i][j] != 0)
                {
                    if (sudoku.gridClone[i][j]) // Chiffres generes par algo
                        SDL_RenderCopy(sudoku.renderer, sudoku.cellTextures[sudoku.grid[i][j] - 1], NULL, &rectangle);
                    else
                    { // nos chiffres
                        SDL_RenderCopy(sudoku.renderer, sudoku.OurCellTextures[sudoku.grid[i][j] - 1], NULL, &rectangle);
                    }
                }
                else
                {
                    for (int k = 0; k < 9; k++)
                    {
                        if (sudoku.megaGrid[i][j][k])
                        {
                            SDL_Rect miniRectangle = {j * CELL_SIZE + CELL_MARGIN + ((k % 3) * (FONT_SIZE / 3)), i * CELL_SIZE + CELL_MARGIN + ((k / 3) * (FONT_SIZE / 3)), FONT_SIZE / 3, FONT_SIZE / 3};
                            SDL_RenderCopy(sudoku.renderer, sudoku.OurCellTextures[k], NULL, &miniRectangle);
                        }
                    }
                }
            }
        }
        SDL_RenderPresent(sudoku.renderer);
    }
    quitGraphics(&sudoku);
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    hInst = hInst;
    hInstPrev = hInstPrev;
    cmdshow = cmdshow;

    int ac = 1;
    char **av = NULL;

    char exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, MAX_PATH);
    av = realloc(av, sizeof(char *) * (ac));
    av[0] = exePath;
    char *token = strtok(cmdline, " ");

    while (token != NULL)
    {
        av = realloc(av, sizeof(char *) * (ac + 1));
        av[ac] = token;
        ac++;
        token = strtok(NULL, " ");
    }

    int result = main(ac, av);

    free(av);
    fclose(stdout);
    FreeConsole();

    return result;
}