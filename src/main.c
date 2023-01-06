#include <stdbool.h>
#include <SDL2/SDL.h>
#include "lib/display.h"
#include "lib/vector.h"
#include "packages/dynamicarray/array.h"
#include "libgen.h"

mesh_t mesh;

bool is_running = false;
vec3_t translateDir = { 0, 0, 0};

float previous_frame_time = 0;

void setup(void) {
  mesh = loadMesh(strcat(dirname(__FILE__), "/assets/cube.obj"));
  mesh.enableBackfaceCulling = true;

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
  mesh.position.x += translateDir.x * 0.05f;
  mesh.position.y += translateDir.y * 0.05f;
  mesh.position.z += translateDir.z * 0.05f;

  mesh.rotation.x += 0.01f;
  mesh.rotation.y += 0.01f;
//  mesh.rotation.z += 0.01f;

  applyTransform(&mesh);
}

void render(void) {
  drawGrid(40, 0xff444444);

  renderMesh(mesh, 0xffeeeeee, 0xff2587be);

/* Triangle Rasterization P.O.C - Start */
//  triangle_t triangle = {
//      .vertexB = { .x = -5, .y = 1, .z= 10 },
//      .vertexC = { .x = 1, .y = 5, .z= 10 },
//      .vertexA = { .x = 6, .y = -5, .z= 10 },
//  };

//  uint32_t fillColor =  0xff00ff00;

//  drawTriangle(triangle, 0xffffffff, &fillColor);
//  drawTriangle(triangle, 0xffffffff, NULL);
/* Triangle Rastearization P.O.C - End */

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

  // Clear dynamic arrays
  array_free(mesh.vertices);
  array_free(mesh.polygons);
  array_free(mesh.transformedPolygons);
  array_free(mesh.faces);

  return 0;
}