#include <stdbool.h>
#include <SDL2/SDL.h>
#include "lib/display.h"
#include "lib/vector.h"
#include "lib/transform.h"
#include "meshes/cube.h"

const int cubeResolution = 4;
const int cubePointCount = cubeResolution * cubeResolution * cubeResolution;
vec3_t cubePoints[cubePointCount];
vec3_t cubeTransformedPoints[cubePointCount];

bool is_running = false;
vec3_t translateDir = { 0, 0, 0};
vec3_t rotateDir = { 0, 0, 0};

float previous_frame_time = 0;

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
  },
  .rotation = {
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
    applyTransform(cubePoints, cubeTransformedPoints, cubePointCount, cubeTransform);
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

            if (event.key.keysym.sym == SDLK_UP) {
                translateDir.y = -1;
            } else if (event.key.keysym.sym == SDLK_DOWN) {
                translateDir.y = 1;
            }

            if (event.key.keysym.sym == SDLK_LEFT) {
                translateDir.x = -1;
            } else if (event.key.keysym.sym == SDLK_RIGHT) {
                translateDir.x = 1;
            }
            break;
        }

        case SDL_KEYUP: {
          if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN) {
            translateDir.y = 0;
          }

          if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
            translateDir.x = 0;
          }
        }
    }
}

void update(void) {
  cubeTransform.position.x += translateDir.x * 0.01f;
  cubeTransform.position.y += translateDir.y * 0.01f;
  cubeTransform.position.z += translateDir.z * 0.01f;

  cubeTransform.rotation.x += 0.01f;
  cubeTransform.rotation.y += 0.01f;
  cubeTransform.rotation.z += 0.01f;

  applyTransform(cubePoints, cubeTransformedPoints, cubePointCount, cubeTransform);
}

void render(void) {
    drawGrid(40, 0xff444444);

    renderCube(cubeTransformedPoints, cubePointCount, 0xfff728e5);

    renderColorBuffer();

    clearColorBuffer(0xff222222);

    SDL_RenderPresent(renderer);
}

int main(void) {
    is_running = initializeWindow(false);

    setup();

    while(is_running) {
      // Fixed frame rate
      float timeToWait = SDL_GetTicks() - previous_frame_time + TARGET_FRAME_TIME;

      if (timeToWait > 0 && timeToWait <= TARGET_FRAME_TIME) {
        SDL_Delay(timeToWait);
      }

      previous_frame_time = SDL_GetTicks();

      handleInput();
      update();
      render();
    }

    destroyWindow();

    return 0;
}