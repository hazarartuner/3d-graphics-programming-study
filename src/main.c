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
  renderMode = SOLID_WITH_WIREFRAME;
  backfaceCulling = BACKFACE_CULLING_ENABLED;

  mesh = loadMesh(strcat(dirname(__FILE__), "/assets/cube.obj"));

  // Set custom color to faces
  mesh.faces[0].color = 0xffff0000;
  mesh.faces[1].color = 0xffff0000;

  mesh.faces[2].color = 0xff00ff00;
  mesh.faces[3].color = 0xff00ff00;

  mesh.faces[4].color = 0xff0000ff;
  mesh.faces[5].color = 0xff0000ff;

  mesh.faces[6].color = 0xffffff00;
  mesh.faces[7].color = 0xffffff00;

  mesh.faces[8].color = 0xfff0f0f0;
  mesh.faces[9].color = 0xfff0f0f0;

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
          // quit from the app
          if (event.key.keysym.sym == SDLK_ESCAPE) {
              is_running = false;
          }

          // move vertically
          if (event.key.keysym.sym == SDLK_UP) {
              translateDir.y = -1;
          } else if (event.key.keysym.sym == SDLK_DOWN) {
              translateDir.y = 1;
          }

          // move horizontally
          if (event.key.keysym.sym == SDLK_LEFT) {
              translateDir.x = -1;
          } else if (event.key.keysym.sym == SDLK_RIGHT) {
              translateDir.x = 1;
          }

          // switch between rendering modes
          if (event.key.keysym.sym == SDLK_1) {
            renderMode = WIREFRAME_AND_VERTEX;
          } else if (event.key.keysym.sym == SDLK_2) {
            renderMode = WIREFRAME;
          } else if (event.key.keysym.sym == SDLK_3) {
            renderMode = SOLID;
          } else if (event.key.keysym.sym == SDLK_4) {
            renderMode = SOLID_WITH_WIREFRAME;
          }

          // Toggle backface culling
          if (event.key.keysym.sym == SDLK_b) {
            if (backfaceCulling == BACKFACE_CULLING_ENABLED) {
              backfaceCulling = BACKFACE_CULLING_DISABLED;
            } else {
              backfaceCulling = BACKFACE_CULLING_ENABLED;
            }
          }
          break;
      }

      // Reset move directions to stop moving
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

  renderMesh(mesh, 0xffff00ff, 0xffeeeeee, -1);

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