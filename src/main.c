#include <stdbool.h>
#include <SDL2/SDL.h>
#include "lib/display.h"
#include "lib/vector.h"
#include "lib/transform.h"
#include "meshes/cube.h"
#include "packages/dynamicarray/array.h"

triangle_t* cube;
triangle_t* cubeTransformed;

bool is_running = false;
vec3_t translateDir = { 0, 0, 0};

double previous_frame_time = 0;

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
    // Crate dynamic arrays
    cubeTransformed = array_hold(cubeTransformed, 12, sizeof (triangle_t));

    colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * windowWidth * windowHeight);
    colorBufferTexture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            windowWidth,
            windowHeight
    );

  cube = createCube();
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
  cubeTransform.position.x += translateDir.x * 0.05f;
  cubeTransform.position.y += translateDir.y * 0.05f;
  cubeTransform.position.z += translateDir.z * 0.05f;

  cubeTransform.rotation.x += 0.01f;
  cubeTransform.rotation.y += 0.01f;
  cubeTransform.rotation.z += 0.01f;

    for (int i = 0; i <  12; ++i) {
        cubeTransformed[i] = rotateTriangle(cube[i], cubeTransform.rotation);
        cubeTransformed[i] = translateTriangle(cubeTransformed[i], cubeTransform.position);
    }
}

void render(void) {
    drawGrid(40, 0xff444444);

    renderMesh(cubeTransformed, 12, 0xfff728e5, 0xffaaaaaa);

    renderColorBuffer();

    clearColorBuffer(0xff222222);

    SDL_RenderPresent(renderer);
}

int main(void) {
    is_running = initializeWindow(false);

    setup();

    while(is_running) {
      // Fixed frame rate
      double timeToWait = SDL_GetTicks() - previous_frame_time + TARGET_FRAME_TIME;

      if (timeToWait > 0 && timeToWait <= TARGET_FRAME_TIME) {
        SDL_Delay(timeToWait);
      }

      previous_frame_time = SDL_GetTicks();

      handleInput();
      update();
      render();
    }

    destroyWindow();

    // Clear dynamic arrays
    array_free(cubeTransformed);
    array_free(cube);

    return 0;
}