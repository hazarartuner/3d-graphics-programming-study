#include <stdbool.h>
#include <SDL2/SDL.h>
#include "lib/display.h"
#include "lib/vector.h"
#include "lib/transform.h"
#include "meshes/cube.h"

const int cubeResolution = 2;
const int cubePointCount = cubeResolution * cubeResolution * cubeResolution;
vec3_t cubePoints[cubePointCount];
vec3_t cubeTransformedPoints[cubePointCount];

bool is_running = false;

dimension_t cubeDimension = {
  .width = 1,
  .height = 1,
  .depth = 1
};

struct Transform cubeTransform = {
  .position = {
    .x = 0,
    .y = 0,
    .z = 0,
  }
};

void setup(void) {
    colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * windowWidth * windowHeight);
    colorBufferTexture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            windowWidth,
            windowHeight
    );

    createCube(cubePoints, cubeDimension, cubeResolution, cubeTransform);
}

void handleInput(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT: {
            is_running = false;
            break;
        }

        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
            }
            break;
        }
    }
}

void update(void) {
  if (cubeTransform.position.x < 2) {
    cubeTransform.position.x += 0.01f;

    translate(cubePoints, cubeTransformedPoints, cubePointCount, cubeTransform);
  }
}

void render(void) {
    drawGrid(40, 0xff444444);

    renderCube(cubeTransformedPoints, cubePointCount);

    renderColorBuffer();

    clearColorBuffer(0xff222222);

    SDL_RenderPresent(renderer);
}

int main(void) {
    is_running = initializeWindow(false);

    setup();

    while(is_running) {
        handleInput();
        update();
        render();
    }

    destroyWindow();

    return 0;
}