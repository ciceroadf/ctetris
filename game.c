#include "game.h"
#include "pieces.h"

#define TARGET_FPS 60
#define BLOCK_SIZE 30
#define BOARD_WIDTH 400 / BLOCK_SIZE
#define BOARD_HEIGHT 600 / BLOCK_SIZE
#define XOFFSET 200
#define YOFFSET BLOCK_SIZE

int BOARD[BOARD_HEIGHT][BOARD_WIDTH] = {{0}};
SDL_Color TETROMINO_COLORS[8] = {
    {0, 0, 0, 255},
    {0, 255, 255, 255}, // I
    {0, 0, 255, 255},   // J
    {255, 165, 0, 255}, // L
    {255, 255, 0, 255}, // O
    {0, 255, 0, 255},   // S
    {160, 32, 240, 255},// T
    {255, 0, 0, 255}    // Z
};


long get_current_time_in_ms()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
}

void populate_board()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        BOARD[15][i] = 1;
    }
}

void draw_tetromino(SDL_Renderer* renderer, Tetromino t)
{
    for (int i = 0; i < 4; i++)
    {
        SDL_Rect rect = {
            .h = BLOCK_SIZE,
            .w = BLOCK_SIZE,
            .x = t.x + (BLOCK_SIZE * t.pieces[i].x) + XOFFSET,
            .y = t.y + (BLOCK_SIZE * t.pieces[i].y) - YOFFSET,
        };

        SDL_Color color = TETROMINO_COLORS[t.type];
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void draw_row(SDL_Renderer* renderer, int row)
{
    int draw_rect = 0;
    int in_board_row = 0;
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        draw_rect = 0;
        if (!(row > 0 && row < BOARD_HEIGHT))
        {
            draw_rect = 1;
            in_board_row = 1;
        }
        else
        {
            if (BOARD[row][i] != 0)
            {
                draw_rect = 1;
            }
        }

        if (draw_rect)
        {
            SDL_Rect rect = {
                .h = BLOCK_SIZE,
                .w = BLOCK_SIZE,
                .x = i * BLOCK_SIZE + XOFFSET,
                .y = row * BLOCK_SIZE - YOFFSET,
            };
            
            if (in_board_row)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else
            {
                SDL_Color color = TETROMINO_COLORS[BOARD[row][i]];
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
            }
            SDL_RenderFillRect(renderer, &rect);
            
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
    
}

void draw_column(SDL_Renderer* renderer, int column)
{
    int draw_rect = 0;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        draw_rect = 0;
        if (!(column < BOARD_WIDTH && column > 0))
        {
            draw_rect = 1;
        }
        else
        {
            if (BOARD[i][column] != 0)
            {
                draw_rect = 1;
            }
        }

        if (draw_rect)
        {
            SDL_Rect rect = {
                .h = BLOCK_SIZE,
                .w = BLOCK_SIZE,
                .x = column * BLOCK_SIZE + XOFFSET - YOFFSET,
                .y = i * BLOCK_SIZE,
            };

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rect);
            
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

void draw_board(SDL_Renderer* renderer)
{
    draw_row(renderer, 0);
    draw_row(renderer, BOARD_HEIGHT);
    draw_column(renderer, 0);
    draw_column(renderer, BOARD_WIDTH + 1);

    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        draw_row(renderer, i);
    }
}

int collided(const Tetromino t, int sdl_key)
{
    for (int i = 0; i < 4; i++) {
        int px = t.x / BLOCK_SIZE + t.pieces[i].x;
        int py = t.y / BLOCK_SIZE + t.pieces[i].y;
    
        if (sdl_key == SDLK_LEFT && (px - 1 < 0 || BOARD[py][px - 1])) return 1;
        if (sdl_key == SDLK_RIGHT && (px + 1 >= BOARD_WIDTH || BOARD[py][px + 1])) return 1;
        if (sdl_key == SDLK_DOWN && (py + 1 >= BOARD_HEIGHT || BOARD[py + 1][px])) return 1;
    }
    return 0;
}

void change_piece(Tetromino* t)
{
    int r_piece = rand() % 7;
    for (int i = 0; i < 4; i++)
    {
        t->pieces[i] = PIECES[r_piece][i];
    }
    t->x = (BLOCK_SIZE * (BOARD_WIDTH / 2)) - BLOCK_SIZE;
    t->y = 0;
    t->type = r_piece + 1;
}

void update_rows(int row)
{
    int board_copy[BOARD_HEIGHT][BOARD_WIDTH] = {{0}};
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            board_copy[i][j] = BOARD[i][j];
        }
    }

    for (int i = row; i > 0; i--)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            BOARD[i][j] = board_copy[i - 1][j];
        }
    }
}

void check_rows(int* score)
{
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        int completed_row = 1;
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (BOARD[i][j] == 0)
            {
                completed_row = 0;
            }
        }

        if (completed_row)
        {
            update_rows(i);
            *score += 100;
        }
    }
}

void rotate(Tetromino* t)
{
    Tetromino test_piece;
    test_piece.x = t->x;
    test_piece.y = t->y;
    for (int i = 0; i < 4; i++) {
        int px = t->pieces[i].x;
        int py = t->pieces[i].y;

        test_piece.pieces[i].x = -py;
        test_piece.pieces[i].y = px;
    }

    if (!collided(test_piece, SDLK_DOWN) && !collided(test_piece, SDLK_LEFT) && !collided(test_piece, SDLK_RIGHT))
    {
        for (int i = 0; i < 4; i++)
        {
            t->pieces[i].x = test_piece.pieces[i].x;
            t->pieces[i].y = test_piece.pieces[i].y;
        }
    }
}

int init_game_loop(SDL_Window* win, SDL_Renderer* renderer)
{
    srand(time(NULL));
    char title[50];
    int running = 1;
    int score = 0;
    Tetromino t;
    t.x = (BLOCK_SIZE * (BOARD_WIDTH / 2)) - BLOCK_SIZE;
    t.y = 20;

    long last_time = get_current_time_in_ms();
    int fps_counter = 0;

    // populate_board();
    change_piece(&t);
    while(running)
    {
        long start_frame_time = get_current_time_in_ms();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_board(renderer);
        draw_tetromino(renderer, t);

        SDL_RenderPresent(renderer);
        SDL_Event ev;
        while(SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (ev.type == SDL_KEYDOWN)
            {
                int key = ev.key.keysym.sym;
                int collision = collided(t, key);
                if (key == SDLK_LEFT && !collision)
                {
                    t.x -= BLOCK_SIZE;
                }

                if (key == SDLK_RIGHT && !collision)
                {
                    t.x += BLOCK_SIZE;
                }

                if (key == SDLK_DOWN && !collision)
                {
                    t.y += BLOCK_SIZE;
                }

                if (key == SDLK_UP)
                {
                    while(!collided(t, SDLK_DOWN))
                    {
                        t.y += BLOCK_SIZE;
                    }
                }

                if (key == SDLK_SPACE)
                {
                    rotate(&t);
                }
            }
        }

        if (collided(t, SDLK_DOWN))
        {

            for (int i = 0; i < 4; i++)
            {
                int px = t.x / BLOCK_SIZE + t.pieces[i].x;
                int py = t.y / BLOCK_SIZE + t.pieces[i].y;

                if (py <= 1)
                {
                    running = 0;
                }

                BOARD[py][px] = t.type;
            }

            check_rows(&score);
            change_piece(&t);
        }

        long end_frame_time = get_current_time_in_ms();
        long elapsed_time = (end_frame_time - start_frame_time);
        fps_counter++;
        if (end_frame_time - last_time >= 1000)
        {
            last_time = end_frame_time;
            t.y += BLOCK_SIZE;
            sprintf(title, "- Tetris - Score: %i - FPS: %i", score, fps_counter);
            SDL_SetWindowTitle(win, title);
            fps_counter = 0;
        }
        
        Uint32 delay_time = 0;
        if ((1000/TARGET_FPS) > elapsed_time)
        {
            delay_time = (Uint32) ((1000/TARGET_FPS) - elapsed_time);
        }

        if (delay_time > 0)
        {
            SDL_Delay(delay_time);
        }

    }
    printf("Game Over\n");
    return 0;
}