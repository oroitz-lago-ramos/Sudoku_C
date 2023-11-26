#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#include "main.h"

#define CELL_SIZE 50
#define CELL_MARGIN 7
#define GRID_SIZE (CELL_SIZE * 9)
#define FONT_SIZE (CELL_SIZE - CELL_MARGIN * 2)
#define WINDOW_WIDTH (GRID_SIZE)
#define WINDOW_HEIGHT (GRID_SIZE)

typedef struct s_sudoku {
    SDL_Window *window;
    SDL_Renderer *renderer;
	SDL_Texture *gridTexture;
	SDL_Texture *cellTextures[9];
    SDL_Texture *OurCellTextures[9];
    

    int posX;
    int posY;
    int clickedPosX;
    int clickedPosY;
    int gameFinished;
    int shiftHeld;
    int gameStarted;

    int range[9];
    int grid[9][9];
    int gridValid[9][9];
    int gridClone[9][9];
    int megaGrid[9][9][9];

    time_t time;

} sudoku;


Point findEmptyCell(int grid[9][9]);
void printSudoku(sudoku *sudoku);
int testNumber(int grid[9][9], Point p, int number);
int removeNumbers(sudoku *sudoku, int num);
void shuffle(sudoku *sudoku);
int solver(sudoku *sudoku, int count, int grid[9][9]);
char **strsplit(char *str, char delimiter);
int findCandidates(sudoku *sudoku);
int findUniqueCandidates(sudoku *sudoku);
int findHiddenUniqueCandidates(sudoku *sudoku);
int idiotSolver(sudoku *sudoku);
int findPointingPairs(sudoku *sudoku);
int findSquarePointingPairs (sudoku *sudoku);
void initGraphics(sudoku *sudoku);
void quitGraphics(sudoku *sudoku);
void eventListener(sudoku *sudoku, int *isOpen);
void sudoku_init (sudoku *sudoku);
int test_fin(sudoku *sudoku);

#endif