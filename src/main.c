#include <stdbool.h>
#include <SDL2/SDL.h>
#include "lib/display.h"
#include "lib/vector.h"
#include "packages/dynamicarray/array.h"
#include "libgen.h"

mesh_t mesh;
mesh_t mesh2;

bool is_running = false;
vec3_t translateDir = { 0, 0, 0};

double previous_frame_time = 0;

void setup(void) {
  mesh = loadMesh(strcat(dirname(__FILE__), "/assets/cube.obj"));
  mesh2 = loadMesh(strcat(dirname(__FILE__), "/assets/cube.obj"));

  mesh2.enableBackfaceCulling = true;

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
  double offsetX = 3;

  mesh.position.x += translateDir.x * 0.05f + offsetX;
  mesh.position.y += translateDir.y * 0.05f;
  mesh.position.z += translateDir.z * 0.05f;

  mesh.rotation.x += 0.01f;
  mesh.rotation.y += 0.01f;
//  mesh.rotation.z += 0.01f;

  mesh2.position.x += translateDir.x * 0.05f - offsetX;
  mesh2.position.y += translateDir.y * 0.05f;
  mesh2.position.z += translateDir.z * 0.05f;

  mesh2.rotation.x += 0.01f;
  mesh2.rotation.y += 0.01f;
//  mesh2.rotation.z += 0.01f;

  applyTransform(&mesh);
  applyTransform(&mesh2);

  mesh.position.x += translateDir.x * 0.05f - offsetX;
  mesh2.position.x += translateDir.x * 0.05f + offsetX;
}

void render(void) {
  drawGrid(40, 0xff444444);

  renderMesh(mesh, 0xfff728e5, 0xffaaaaaa);
  renderMesh(mesh2, 0xfff728e5, 0xffaaaaaa);

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
  array_free(mesh.vertices);
  array_free(mesh.polygons);
  array_free(mesh.transformedPolygons);
  array_free(mesh.faces);

  return 0;
}