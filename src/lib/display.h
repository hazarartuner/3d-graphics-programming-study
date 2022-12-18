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

bool initializeWindow(bool isFullScreen);
void destroyWindow(void);
void renderColorBuffer(void);
void renderMesh(mesh_t mesh, uint32_t vertexColor, uint32_t edgeColor);
void clearColorBuffer(uint32_t color);
void drawPixel(int x, int y, uint32_t color);
void drawGrid(int space, uint32_t gridColor);
void drawRect(int posX, int posY, int width, int height, uint32_t fillColor);
void drawLine(vec2_t p1, vec2_t p2, uint32_t color);

#endif  // INC_3DGP_DISPLAY_H
