#include <stdbool.h>
#include <SDL2/SDL.h>
#include "lib/mesh.h"
#include "lib/display.h"
#include "lib/vector.h"
#include "meshes/cube.h"
#include "packages/dynamicarray/array.h"

mesh_t cube;

bool is_running = false;
vec3_t translateDir = { 0, 0, 0};

double previous_frame_time = 0;

void setup(void) {
  cube = createCube();

    colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * windowWidth * windowHeight);
    colorBufferTexture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            windowWidth,
            windowHeight
    );
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
  cube.position.x += translateDir.x * 0.05f;
  cube.position.y += translateDir.y * 0.05f;
  cube.position.z += translateDir.z * 0.05f;

  cube.rotation.x += 0.01f;
  cube.rotation.y += 0.01f;
  cube.rotation.z += 0.01f;

  applyTransform(&cube);
}

void render(void) {
    drawGrid(40, 0xff444444);

    renderMesh(cube.transformedPolygons, 12, 0xfff728e5, 0xffaaaaaa);

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
    array_free(cube.vertices);
    array_free(cube.polygons);
    array_free(cube.transformedPolygons);
    array_free(cube.faces);

    return 0;
}