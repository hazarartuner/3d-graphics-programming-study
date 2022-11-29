//
// Created by Mehmet Hazar Artuner on 18.11.2022.
//

#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

int window_width = 800;
int window_height = 600;

bool initialize_window(bool isFullScreen) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Initializing SDL error.\n");
        return false;
    }

    // Set width and height of SDL window
    SDL_DisplayMode displayMode;
    SDL_GetDesktopDisplayMode(0, &displayMode);

    window_width = displayMode.w;
    window_height = displayMode.h;

    // Create SDL window
    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            window_width,
            window_height,
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

void destroy_window(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void render_color_buffer(void) {
    SDL_UpdateTexture(
            color_buffer_texture,
            NULL,
            color_buffer,
            (int) (window_width * sizeof(uint32_t))
    );
    SDL_RenderCopy(
            renderer,
            color_buffer_texture,
            NULL,
            NULL
    );
}

void clear_color_buffer(uint32_t color) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void draw_pixel(int x, int y, uint32_t color) {
    if (x > 0 && x < window_width && y > 0 && y < window_height) {
        color_buffer[(window_width * y) + x] = color;
    }
}

void draw_grid(int space, uint32_t gridColor) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            if ((y > 0 && y % space == 0) || (x > 0 && x % space == 0)) {
                draw_pixel(x, y, gridColor);
            }
        }
    }
}

void draw_rect(int posX, int posY, int width, int height, uint32_t fillColor) {
    int maxY = posY + height;
    maxY = maxY <= window_height ? maxY : window_height;

    int maxX = posX + width;
    maxX = maxX <= window_width ? maxX : window_width;

    for (int y = posY; y < maxY; y++) {
        for (int x = posX; x < maxX; x++) {
            draw_pixel(x, y, fillColor);
        }
    }
}