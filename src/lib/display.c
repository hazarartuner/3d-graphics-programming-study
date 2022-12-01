//
// Created by Mehmet Hazar Artuner on 18.11.2022.
//

#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

uint32_t* colorBuffer = NULL;
SDL_Texture* colorBufferTexture = NULL;

int windowWidth = 800;
int windowHeight = 600;

bool initializeWindow(bool isFullScreen) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Initializing SDL error.\n");
        return false;
    }

    // Set width and height of SDL window
    SDL_DisplayMode displayMode;
    SDL_GetDesktopDisplayMode(0, &displayMode);

    windowWidth = displayMode.w;
    windowHeight = displayMode.h;

    // Create SDL window
    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_BORDERLESS
    );

    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    // Create SDL renderer
    renderer = SDL_CreateRenderer(
            window,
            -1, // get the first monitor
            0
    );

    if (isFullScreen) {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }

    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    return true;
}

void destroyWindow(void) {
    free(colorBuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderColorBuffer(void) {
    SDL_UpdateTexture(
            colorBufferTexture,
            NULL,
            colorBuffer,
            (int) (windowWidth * sizeof(uint32_t))
    );
    SDL_RenderCopy(
            renderer,
            colorBufferTexture,
            NULL,
            NULL
    );
}

void clearColorBuffer(uint32_t color) {
    for (int y = 0; y < windowHeight; y++) {
        for (int x = 0; x < windowWidth; x++) {
            colorBuffer[(windowWidth * y) + x] = color;
        }
    }
}

void drawPixel(int x, int y, uint32_t color) {
    if (x > 0 && x < windowWidth && y > 0 && y < windowHeight) {
        colorBuffer[(windowWidth * y) + x] = color;
    }
}

void drawGrid(int space, uint32_t gridColor) {
    for (int y = 0; y < windowHeight; y++) {
        for (int x = 0; x < windowWidth; x++) {
            if ((y > 0 && y % space == 0) || (x > 0 && x % space == 0)) {
                drawPixel(x, y, gridColor);
            }
        }
    }
}

void drawRect(int posX, int posY, int width, int height, uint32_t fillColor) {
    int maxY = posY + height;
    maxY = maxY <= windowHeight ? maxY : windowHeight;

    int maxX = posX + width;
    maxX = maxX <= windowWidth ? maxX : windowWidth;

    for (int y = posY; y < maxY; y++) {
        for (int x = posX; x < maxX; x++) {
            drawPixel(x, y, fillColor);
        }
    }
}