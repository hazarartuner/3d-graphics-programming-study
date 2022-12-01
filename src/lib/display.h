//
// Created by Mehmet Hazar Artuner on 18.11.2022.
//

#ifndef INC_3DGP_DISPLAY_H
#define INC_3DGP_DISPLAY_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern uint32_t* colorBuffer;
extern SDL_Texture* colorBufferTexture;

extern int windowWidth;
extern int windowHeight;

bool initializeWindow(bool isFullScreen);
void destroyWindow(void);
void renderColorBuffer(void);
void clearColorBuffer(uint32_t color);
void drawPixel(int x, int y, uint32_t color);
void drawGrid(int space, uint32_t gridColor);
void drawRect(int posX, int posY, int width, int height, uint32_t fillColor);

#endif //INC_3DGP_DISPLAY_H
