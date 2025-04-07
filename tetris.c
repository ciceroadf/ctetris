#include "game.h"
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600


int main(void)
{
    SDL_Window* win = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!win)
    {
        printf("Couldn't create window.\n");
        return 1;
    }

    SDL_Renderer* rndr = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

    if (!rndr)
    {
        printf("Couldn't create renderer.\n");
        return 1;
    }

    init_game_loop(win, rndr);

    SDL_DestroyRenderer(rndr);
    SDL_DestroyWindow(win);
    return 0;
}