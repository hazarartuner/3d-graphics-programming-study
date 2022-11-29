#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

const int N_POINTS = 9 * 9 * 9;
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];
float fov_factor = 10;

bool is_running = false;

void setup(void) {
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
    color_buffer_texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            window_width,
            window_height
    );
}

void process_input(void) {
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
            break;
        }
    }
}

vec2_t project(vec3_t point) {
    vec2_t projected_point = {
        .x = point.x,
        .y = point.y
    };

    return projected_point;
}


void update(void) {

    int point_index = 0;

    if (fov_factor < 512) {
      fov_factor += 1;
    }

    for (float x=-1; x<=1; x += 0.25f) {
        for (float y=-1; y<=1; y += 0.25f) {
            for (float z=-1; z<=1; z += 0.25f) {
                vec3_t point = {
                        .x = x * 0.25f * fov_factor,
                        .y = y * 0.25f * fov_factor,
                        .z = z * 0.25f * fov_factor
                };

                cube_points[point_index] = point;

                projected_points[point_index] = project(point);

                point_index += 1;
            }
        }
    }
}

void render(void) {
    draw_grid(40, 0xff444444);

    for (int i = 0; i < N_POINTS; ++i) {
        vec2_t point = projected_points[i];

        draw_rect(
            point.x + window_width / 2,
            point.y + window_height / 2,
            4,
            4,
            0xfff728e5
        );
    }

    render_color_buffer();

    clear_color_buffer(0xff222222);

    SDL_RenderPresent(renderer);
}

int main(void) {
    is_running = initialize_window(false);

    setup();

    while(is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}