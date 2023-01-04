//
// Created by Mehmet Hazar Artuner on 18.11.2022.
//

#include "display.h"

const float FPS = 60;
const float TARGET_FRAME_TIME = (1000.0f / FPS);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

uint32_t *colorBuffer = NULL;
SDL_Texture *colorBufferTexture = NULL;

int windowWidth = 800;
int windowHeight = 600;

bool initializeWindow(bool isFullScreen) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Initializing SDL error.\n");
    return false;
  }

  // Set width and height of SDL window
  SDL_DisplayMode displayMode;
  SDL_GetDesktopDisplayMode(0, &displayMode);

  windowWidth = displayMode.w;
  windowHeight = displayMode.h;

  // Create SDL window
  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);

  if (!window) {
    fprintf(stderr, "Error creating SDL window.\n");
    return false;
  }

  // Create SDL renderer
  renderer = SDL_CreateRenderer(window,
                                -1,  // get the first monitor
                                0);

  if (isFullScreen) {
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
  }

  if (!renderer) {
    fprintf(stderr, "Error creating SDL renderer.\n");
    return false;
  }

  return true;
}

void destroyWindow(void) {
  free(colorBuffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void renderColorBuffer(void) {
  SDL_UpdateTexture(colorBufferTexture, NULL, colorBuffer,
                    (int)(windowWidth * sizeof(uint32_t)));
  SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void clearColorBuffer(uint32_t color) {
  for (int y = 0; y < windowHeight; y++) {
    for (int x = 0; x < windowWidth; x++) {
      colorBuffer[(windowWidth * y) + x] = color;
    }
  }
}

void renderMesh(mesh_t mesh, uint32_t vertexColor, uint32_t edgeColor) {
  for (int i = 0; i < mesh.faceCount; i++) {
    if (shouldCullTriangle(mesh.transformedPolygons[i])) {
      continue;
    }

    vec2_t projectedPoints[3];

    // Project points
    projectedPoints[0] =
        projectAsPerspective(mesh.transformedPolygons[i].vertexA);
    projectedPoints[1] =
        projectAsPerspective(mesh.transformedPolygons[i].vertexB);
    projectedPoints[2] =
        projectAsPerspective(mesh.transformedPolygons[i].vertexC);

    // Draw line between projected points to render triangle edges
    drawLine(projectedPoints[0], projectedPoints[1], edgeColor);
    drawLine(projectedPoints[1], projectedPoints[2], edgeColor);
    drawLine(projectedPoints[2], projectedPoints[0], edgeColor);

    // Draw vertexes
    for (int j = 0; j < 3; j++) {
      drawRect(projectedPoints[j].x, projectedPoints[j].y, 4, 4, vertexColor);
    }
  }
}

void drawPixel(int x, int y, uint32_t color) {
  if (x > 0 && x < windowWidth && y > 0 && y < windowHeight) {
    colorBuffer[(windowWidth * y) + x] = color;
  }
}

void drawGrid(int space, uint32_t gridColor) {
  for (int y = 0; y < windowHeight; y++) {
    for (int x = 0; x < windowWidth; x++) {
      if ((y > 0 && y % space == 0) || (x > 0 && x % space == 0)) {
        drawPixel(x, y, gridColor);
      }
    }
  }
}

void drawRect(int posX, int posY, int width, int height, uint32_t fillColor) {
  int maxY = posY + height;
  maxY = maxY <= windowHeight ? maxY : windowHeight;

  int maxX = posX + width;
  maxX = maxX <= windowWidth ? maxX : windowWidth;

  for (int y = posY; y < maxY; y++) {
    for (int x = posX; x < maxX; x++) {
      drawPixel(x, y, fillColor);
    }
  }
}

void drawLine(vec2_t p1, vec2_t p2, uint32_t color) {
  int delta_x = p2.x - p1.x;
  int delta_y = p2.y - p1.y;

  // By choosing the longest side, we can calculate the increase
  // ratio of the x and y points correctly.
  int longest_side_length =
      abs(delta_x) > abs(delta_y) ? abs(delta_x) : abs(delta_y);

  double x_ct = delta_x / (double)longest_side_length;
  double y_ct = delta_y / (double)longest_side_length;

  double current_x = p1.x;
  double current_y = p1.y;

  for (int i = 0; i <= longest_side_length; i++) {
    drawPixel((int)round(current_x), (int)round(current_y), color);

    current_x += x_ct;
    current_y += y_ct;
  }
}

bool shouldCullTriangle(triangle_t triangle) {
  vec3_t a = vec3_sub(triangle.vertexB, triangle.vertexA);
  vec3_t b = vec3_sub(triangle.vertexC, triangle.vertexA);

  vec3_t normal = vec3_cross(a, b);

  vec3_t cameraRayVec = vec3_sub(cameraPosition, triangle.vertexA);

  return vec3_dot(normal, cameraRayVec) <= 0;
}