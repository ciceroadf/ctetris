# CTetris

A simple Tetris implementation written in C using the [SDL2](https://www.libsdl.org/) library.

## 🎮 Features

- Classic Tetris gameplay
- Colored tetrominoes with individual styles
- Piece rotation and movement
- Collision detection
- Line clearing and scoring
- Game over detection
- Runs at a consistent 60 FPS

## 📦 Requirements

- SDL2 library
- C compiler (e.g., `gcc`, `clang`)

### 🛠 Install SDL2

#### On Ubuntu/Debian:

```bash
sudo apt update
sudo apt install libsdl2-dev
```

#### On macOS (using Homebrew):

```bash
brew install sdl2
```

#### On Windows:

- Install [MSYS2](https://www.msys2.org/)
- Follow SDL2 install instructions in MSYS2 documentation

## 🔧 Build Instructions

Clone the repo and build the game:

```bash
git clone https://github.com/yourusername/ctetris.git
cd ctetris
gcc tetris.c game.c -o tetris -lSDL2
```

This will produce an executable called `ctetris`.

## 🚀 Run the Game

```bash
./ctetris
```

## 🎮 Controls

| Key         | Action           |
|-------------|------------------|
| `←`         | Move Left        |
| `→`         | Move Right       |
| `↓`         | Soft Drop        |
| `↑`         | Hard Drop        |
| `Space`     | Rotate Piece     |

## 🖼️ Screenshots

*(Add screenshots or a gif here)*

## 📁 Project Structure

```
.
├── game.c        # Main game loop and rendering logic
├── game.h        # Game declarations
├── pieces.c      # Tetromino definitions
├── pieces.h      # Tetromino header
├── Makefile      # Build script
└── README.md     # You're here!
```

