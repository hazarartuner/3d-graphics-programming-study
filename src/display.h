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

extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;

extern int window_width;
extern int window_height;

bool initialize_window(bool isFullScreen);
void destroy_window(void);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void draw_grid(int space, uint32_t gridColor);
void draw_rect(int posX, int posY, int width, int height, uint32_t fillColor);

#endif //INC_3DGP_DISPLAY_H
