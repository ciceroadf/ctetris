typedef struct Piece
{
    int x;
    int y;
} Piece;

typedef struct Tetromino
{
    int x;
    int y;
    struct Piece pieces[4];
    int type;
} Tetromino;

struct Piece PIECES[7][4] = {
    // I
    {
        {.x = 0, .y = 1},
        {.x = 0, .y = 0},
        {.x = 0, .y = -1},
        {.x = 0, .y = -2},
    },
    // O
    {
        {.x = 0, .y = 0},
        {.x = 1, .y = 0},
        {.x = 0, .y = 1},
        {.x = 1, .y = 1},
    },
    // T
    {
        {.x = -1, .y = 0},
        {.x = 0,  .y = 0},
        {.x = 1,  .y = 0},
        {.x = 0,  .y = -1},
    },
    // S
    {
        {.x = 0,  .y = 0},
        {.x = 1,  .y = 0},
        {.x = -1, .y = -1},
        {.x = 0,  .y = -1},
    },
    // Z
    {
        {.x = -1, .y = 0},
        {.x = 0,  .y = 0},
        {.x = 0,  .y = -1},
        {.x = 1,  .y = -1},
    },
    // J
    {
        {.x = -1, .y = 0},
        {.x = 0,  .y = 0},
        {.x = 1,  .y = 0},
        {.x = 1,  .y = -1},
    },
    // L
    {
        {.x = -1, .y = 0},
        {.x = 0,  .y = 0},
        {.x = 1,  .y = 0},
        {.x = -1, .y = -1},
    }
};