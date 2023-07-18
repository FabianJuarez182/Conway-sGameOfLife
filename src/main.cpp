#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "framebuffer.h"
#include "point.h"
#include "color.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

constexpr size_t BOARD_WIDTH = 100;
constexpr size_t BOARD_HEIGHT = 100;

bool board[BOARD_WIDTH][BOARD_HEIGHT];

Color cellColor(255, 255, 255);  // Color rojo vino
Color backgroundColor(0, 0, 0);  // Color de fondo combinado

// Function to set a specific pixel in the framebuffer to the specified color
void point(int x, int y, const Color& color) {
    if (x >= 0 && x < FRAMEBUFFER_WIDTH && y >= 0 && y < FRAMEBUFFER_HEIGHT) {
        framebuffer[y * FRAMEBUFFER_WIDTH + x] = color;
    }
}

// Function to count the number of live neighbors for a given cell
int countLiveNeighbors(int x, int y) {
    int liveNeighbors = 0;

    // Check the eight neighboring cells
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0)
                continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < BOARD_WIDTH && ny >= 0 && ny < BOARD_HEIGHT) {
                if (board[nx][ny])
                    liveNeighbors++;
            }
        }
    }

    return liveNeighbors;
}

// Function to update the board for the next generation
void updateBoard() {
    bool newBoard[BOARD_WIDTH][BOARD_HEIGHT];

    // Iterate over each cell in the board
    for (int x = 0; x < BOARD_WIDTH; ++x) {
        for (int y = 0; y < BOARD_HEIGHT; ++y) {
            int liveNeighbors = countLiveNeighbors(x, y);

            // Apply the rules of Conway's Game of Life
            if (board[x][y]) {
                if (liveNeighbors < 2 || liveNeighbors > 3)
                    newBoard[x][y] = false;  // Cell dies
                else
                    newBoard[x][y] = true;   // Cell survives
            } else {
                if (liveNeighbors == 3)
                    newBoard[x][y] = true;   // Cell reproduces
                else
                    newBoard[x][y] = false;  // Cell remains dead
            }
        }
    }

    // Update the board
    for (int x = 0; x < BOARD_WIDTH; ++x) {
        for (int y = 0; y < BOARD_HEIGHT; ++y) {
            board[x][y] = newBoard[x][y];
        }
    }
}

// Function to initialize the board with random live cells and specific patterns
void initializeBoard() {
    // Clear the board
    for (int x = 0; x < BOARD_WIDTH; ++x) {
        for (int y = 0; y < BOARD_HEIGHT; ++y) {
            board[x][y] = false;
        }
    }

    // Randomly add specific patterns to the board
    for (int i = 0; i < 1000; ++i) {
        int pattern = rand() % 11;

        int startX = rand() % (BOARD_WIDTH - 10);
        int startY = rand() % (BOARD_HEIGHT - 10);

        if (pattern == 0) {
            // Block
            board[startX][startY] = true;
            board[startX][startY + 1] = true;
            board[startX + 1][startY] = true;
            board[startX + 1][startY + 1] = true;
        } else if (pattern == 1) {
            // Bee-hive
            board[startX + 1][startY] = true;
            board[startX + 2][startY] = true;
            board[startX][startY + 1] = true;
            board[startX + 3][startY + 1] = true;
            board[startX + 1][startY + 2] = true;
            board[startX + 2][startY + 2] = true;
        } else if (pattern == 2) {
            // Loaf
            board[startX + 1][startY] = true;
            board[startX + 2][startY] = true;
            board[startX][startY + 1] = true;
            board[startX + 3][startY + 1] = true;
            board[startX + 1][startY + 2] = true;
            board[startX + 3][startY + 2] = true;
            board[startX + 2][startY + 3] = true;
        } else if (pattern == 3) {
            // Boat
            board[startX][startY] = true;
            board[startX + 1][startY] = true;
            board[startX][startY + 1] = true;
            board[startX + 2][startY + 1] = true;
            board[startX + 1][startY + 2] = true;
        } else if (pattern == 4) {
            // Tub
            board[startX + 1][startY] = true;
            board[startX][startY + 1] = true;
            board[startX + 2][startY + 1] = true;
            board[startX + 1][startY + 2] = true;
        } else if (pattern == 5) {
            // Blinker
            board[startX][startY] = true;
            board[startX + 1][startY] = true;
            board[startX + 2][startY] = true;
        } else if (pattern == 6) {
            // Toad
            board[startX + 1][startY] = true;
            board[startX + 2][startY] = true;
            board[startX + 3][startY] = true;
            board[startX][startY + 1] = true;
            board[startX + 1][startY + 1] = true;
            board[startX + 2][startY + 1] = true;
        } else if (pattern == 7) {
            // Beacon
            board[startX][startY] = true;
            board[startX + 1][startY] = true;
            board[startX][startY + 1] = true;
            board[startX + 3][startY + 2] = true;
            board[startX + 2][startY + 3] = true;
            board[startX + 3][startY + 3] = true;
        } else if (pattern == 8) {
            // Pulsar
            int offset = 3;
            for (int i = 0; i < 3; ++i) {
                board[startX + i][startY + offset] = true;
                board[startX + i + 4][startY + offset] = true;
                board[startX + i + 9][startY + offset] = true;
                board[startX + i][startY + offset + 5] = true;
                board[startX + i + 4][startY + offset + 5] = true;
                board[startX + i + 9][startY + offset + 5] = true;
                offset--;
            }
            offset = 3;
            for (int i = 0; i < 3; ++i) {
                board[startX + offset][startY + i] = true;
                board[startX + offset][startY + i + 4] = true;
                board[startX + offset][startY + i + 9] = true;
                board[startX + offset + 5][startY + i] = true;
                board[startX + offset + 5][startY + i + 4] = true;
                board[startX + offset + 5][startY + i + 9] = true;
                offset--;
            }
        } else if (pattern == 9) {
            // Penta-decathlon
            int offset = 1;
            for (int i = 0; i < 7; ++i) {
                board[startX][startY + offset] = true;
                board[startX + 1][startY + offset] = true;
                board[startX + 2][startY + offset] = true;
                offset++;
            }
        } else if (pattern == 10) {
            // Glider
            board[startX + 1][startY] = true;
            board[startX + 2][startY + 1] = true;
            board[startX][startY + 2] = true;
            board[startX + 1][startY + 2] = true;
            board[startX + 2][startY + 2] = true;
        }
    }
}

void renderBuffer(SDL_Renderer* renderer) {
    // Create a texture
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,
        FRAMEBUFFER_WIDTH,
        FRAMEBUFFER_HEIGHT
    );

    // Update the texture with the pixel data from the framebuffer
    SDL_UpdateTexture(
        texture,
        NULL,
        framebuffer,
        FRAMEBUFFER_WIDTH * sizeof(Color)
    );

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}

void render(SDL_Renderer* renderer) {
    // Clear the framebuffer with the background color
    std::fill(framebuffer, framebuffer + FRAMEBUFFER_SIZE, backgroundColor);

    // Draw the board
    for (int x = 0; x < BOARD_WIDTH; ++x) {
        for (int y = 0; y < BOARD_HEIGHT; ++y) {
            if (board[x][y]) {
                // Draw live cells with the specified color
                point(x, y, cellColor);
            }
        }
    }

    // Update the board for the next generation
    updateBoard();

    // Render the framebuffer to the screen
    renderBuffer(renderer);
}

int main() {
    // Initialize the random seed
    srand(time(NULL));

    // Initialize the board with random live cells and specific patterns
    initializeBoard();

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Game of Life", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Call our render function
        render(renderer);

        // Present the frame buffer to the screen
        SDL_RenderPresent(renderer);

        // Delay to limit the frame rate
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
