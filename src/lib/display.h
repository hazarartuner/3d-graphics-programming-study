//
// Created by Mehmet Hazar Artuner on 18.11.2022.
//

#ifndef INC_3DGP_DISPLAY_H
#define INC_3DGP_DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include "../lib/camera.h"
#include "../lib/mesh.h"
#include "triangle.h"
#include "vector.h"

const float FPS;
const float TARGET_FRAME_TIME;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern uint32_t *colorBuffer;
extern SDL_Texture *colorBufferTexture;

extern int windowWidth;
extern int windowHeight;

enum RENDER_MODE {
  WIREFRAME_AND_VERTEX = 1,
  WIREFRAME = 2,
  SOLID = 3,
  SOLID_WITH_WIREFRAME = 4,
} renderMode;

enum BACKFACE_CULLING {
  BACKFACE_CULLING_ENABLED = 1,
  BACKFACE_CULLING_DISABLED = 2,
} backfaceCulling;

// enum RENDER_MODE renderMode = SOLID_WITH_WIREFRAME;

bool initializeWindow(bool isFullScreen);
void destroyWindow(void);
void renderColorBuffer(void);
void renderMesh(mesh_t mesh, uint32_t vertexColor, uint32_t edgeColor,
                uint32_t fillColor);
void clearColorBuffer(uint32_t color);
void drawPixel(int x, int y, uint32_t color);
void drawGrid(int space, uint32_t gridColor);
void drawRect(vec2_t pos, int width, int height, uint32_t fillColor,
              bool centerIsOrigin);
void drawLine(vec2_t p1, vec2_t p2, uint32_t color);
void drawFlatBottomTriangle(vec2_t p1, vec2_t p2, vec2_t p3,
                            uint32_t fillColor);
void drawFlatTopTriangle(vec2_t p1, vec2_t p2, vec2_t p3, uint32_t fillColor);
void drawTriangle(triangle_t triangle, uint32_t vertexColor, uint32_t edgeColor,
                  uint32_t fillColor);
bool shouldCullTriangle(triangle_t triangle);

#endif  // INC_3DGP_DISPLAY_H
