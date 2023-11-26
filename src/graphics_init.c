#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "fonctions.h"

void init_grid_surface(sudoku *sudoku)
{

	sudoku->gridTexture = SDL_CreateTexture(sudoku->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_SetRenderTarget(sudoku->renderer, sudoku->gridTexture);

	// SDL_SetRenderDrawBlendMode(sudoku->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sudoku->renderer, 99, 183, 183, 255);
	SDL_RenderClear(sudoku->renderer);

	/* 	for (int i = 0; i < 3; i++)
	   {
		   for (int j = 0; j < 3; j++)
		   {
			   SDL_SetRenderDrawColor(sudoku->renderer, 64, 93, 115, 255);
			   SDL_Rect rectangle = {i * BigCellSize, j * BigCellSize, BigCellSize, BigCellSize};
			   SDL_RenderDrawRect(sudoku->renderer, &rectangle);
			   for (int k = 0; k < 3; k++)
			   {
				   for (int l = 0; l < 3; l++)
				   {
					   SDL_SetRenderDrawColor(sudoku->renderer, 51, 128, 145, 255);
					   SDL_Rect miniRectangle = {(i *BigCellSize) + (k * CELL_SIZE), (j * BigCellSize) + (l * CELL_SIZE), CELL_SIZE, CELL_SIZE};
					   SDL_RenderDrawRect(sudoku->renderer, &miniRectangle);
				   }
			   }
		   }
	   } */

	SDL_SetRenderDrawColor(sudoku->renderer, 51, 128, 145, 255);
	for (int x = 0; x < 1 + GRID_SIZE * CELL_SIZE; x += CELL_SIZE)
	{
		SDL_RenderDrawLine(sudoku->renderer, x, 0, x, GRID_SIZE);
	}

	for (int y = 0; y < 1 + GRID_SIZE * CELL_SIZE; y += CELL_SIZE)
	{
		SDL_RenderDrawLine(sudoku->renderer, 0, y, GRID_SIZE, y);
	}

	SDL_SetRenderDrawColor(sudoku->renderer, 0, 0, 0, 255);
	for (int x = 0; x < 1 + GRID_SIZE * CELL_SIZE; x += GRID_SIZE / 3)
	{
		SDL_RenderDrawLine(sudoku->renderer, x, 0, x, GRID_SIZE);
	}

	for (int y = 0; y < 1 + GRID_SIZE * CELL_SIZE; y += GRID_SIZE / 3)
	{
		SDL_RenderDrawLine(sudoku->renderer, 0, y, GRID_SIZE, y);
	}

	// SDL_RenderPresent(sudoku->renderer);

	SDL_SetRenderTarget(sudoku->renderer, NULL);
}

void init_font(sudoku *sudoku)
{
	TTF_Font *font = TTF_OpenFont("arial_narrow_7.ttf", FONT_SIZE);

	// Initialisation de font pour les chiffres generes par notre algo
	for (int i = 0; i < 9; i++)
	{
		char str[2];
		str[0] = i + '1';
		str[1] = 0;
		SDL_Surface *text = TTF_RenderText_Blended(font, str, (SDL_Color){0, 0, 0, 255});
		sudoku->cellTextures[i] = SDL_CreateTextureFromSurface(sudoku->renderer, text);
		SDL_FreeSurface(text);
	}

	// Initialisation de font pour les chiffres entrés par l'utilisateur et les mini chiffres(anotations)
	for (int i = 0; i < 9; i++)
	{
		char str[2];
		str[0] = i + '1';
		str[1] = 0;
		SDL_Surface *text = TTF_RenderText_Blended(font, str, (SDL_Color){100, 100, 150, 255});
		sudoku->OurCellTextures[i] = SDL_CreateTextureFromSurface(sudoku->renderer, text);
		SDL_FreeSurface(text);
	}
	TTF_CloseFont(font);
}

void initGraphics(sudoku *sudoku)
{
	sudoku_init(sudoku);
	
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	sudoku->window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	sudoku->renderer = SDL_CreateRenderer(sudoku->window, -1, SDL_RENDERER_ACCELERATED);
	init_grid_surface(sudoku);
	init_font(sudoku);
}

void quitGraphics(sudoku *sudoku)
{
	SDL_DestroyRenderer(sudoku->renderer);
	SDL_DestroyWindow(sudoku->window);
	SDL_DestroyTexture(sudoku->gridTexture);
	for (int i = 0; i < 9; i++)
	{
		SDL_DestroyTexture(sudoku->cellTextures[i]);
	}
	for (int i = 0; i < 9; i++)
	{
		SDL_DestroyTexture(sudoku->OurCellTextures[i]);
	}
	TTF_Quit();
	SDL_Quit();
}