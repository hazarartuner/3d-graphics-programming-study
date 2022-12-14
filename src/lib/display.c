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

void renderMesh(mesh_t mesh, uint32_t vertexColor, uint32_t edgeColor,
                uint32_t fillColor) {
  sortTrianglesByAverageDepth(mesh.transformedPolygons, mesh.faceCount, true);

  for (int i = 0; i < mesh.faceCount; i++) {
    if (backfaceCulling == BACKFACE_CULLING_ENABLED &&
        shouldCullTriangle(mesh.transformedPolygons[i])) {
      continue;
    }

    uint32_t color =
        fillColor == -1 ? mesh.transformedPolygons[i].color : fillColor;

    drawTriangle(mesh.transformedPolygons[i], vertexColor, edgeColor, color);
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

void drawRect(vec2_t pos, int width, int height, uint32_t fillColor,
              bool centerIsOrigin) {
  int posX = centerIsOrigin ? pos.x - width / 2 : pos.x;
  int posY = centerIsOrigin ? pos.y - height / 2 : pos.y;

  int maxX = posX + width;
  maxX = maxX <= windowWidth ? maxX : windowWidth;

  int maxY = posY + height;
  maxY = maxY <= windowHeight ? maxY : windowHeight;

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

  float x_ct = delta_x / (float)longest_side_length;
  float y_ct = delta_y / (float)longest_side_length;

  float current_x = p1.x;
  float current_y = p1.y;

  for (int i = 0; i <= longest_side_length; i++) {
    drawPixel((int)round(current_x), (int)round(current_y), color);

    current_x += x_ct;
    current_y += y_ct;
  }
}

void drawFlatBottomTriangle(vec2_t p1, vec2_t p2, vec2_t p3,
                            uint32_t fillColor) {
  // Using raw float variables cause issue, therefore
  // I had to create and use int versions for each property.
  int x1 = (int)p1.x;
  int y1 = (int)p1.y;
  int x2 = (int)p2.x;
  int y2 = (int)p2.y;
  int x3 = (int)p3.x;
  int y3 = (int)p3.y;

  // Calculate slopes for each corner
  float inverse_slope_1 = (float)(x1 - x2) / (float)(y1 - y2);
  float inverse_slope_2 = (float)(x1 - x3) / (float)(y1 - y3);

  vec2_t startPoint = p1;
  vec2_t endPoint = p1;

  int maxWidth = abs(x3 - x2);

  for (int y = y1; y <= y2; y++) {
    startPoint.x += inverse_slope_1;
    startPoint.y = (float)y;

    endPoint.x += inverse_slope_2;
    endPoint.y = (float)y;

    int width = abs(startPoint.x - endPoint.x);

    // fix overflowed values
    if (width > maxWidth) {
      startPoint.x = x2;
      endPoint.x = x3;
    }

    drawLine(startPoint, endPoint, fillColor);
  }
}

void drawFlatTopTriangle(vec2_t p1, vec2_t p2, vec2_t p3, uint32_t fillColor) {
  // Using raw float variables cause issue, therefore
  // I had to create and use int versions for each property.
  int x1 = (int)p1.x;
  int y1 = (int)p1.y;
  int x2 = (int)p2.x;
  int y2 = (int)p2.y;
  int x3 = (int)p3.x;
  int y3 = (int)p3.y;

  float inverse_slope_1 = (float)(x2 - x1) / (float)(y2 - y1);
  float inverse_slope_2 = (float)(x2 - x3) / (float)(y2 - y3);

  vec2_t startPoint = p2;
  vec2_t endPoint = p2;

  int maxWidth = abs(x3 - x1);

  for (int y = y2; y >= y1; y--) {
    startPoint.x -= inverse_slope_1;
    startPoint.y = (float)y;

    endPoint.x -= inverse_slope_2;
    endPoint.y = (float)y;

    int width = abs(startPoint.x - endPoint.x);

    // fix overflowed values
    if (width > maxWidth) {
      startPoint.x = x1;
      endPoint.x = x3;
    }

    drawLine(startPoint, endPoint, fillColor);
  }
}

void drawTriangle(triangle_t triangle, uint32_t vertexColor, uint32_t edgeColor,
                  uint32_t fillColor) {
  vec2_t projectedPoints[3];

  projectedPoints[0] = projectAsPerspective(triangle.vertices[0]);
  projectedPoints[1] = projectAsPerspective(triangle.vertices[1]);
  projectedPoints[2] = projectAsPerspective(triangle.vertices[2]);

  // Fill the vertex
  if (renderMode == SOLID || renderMode == SOLID_WITH_WIREFRAME) {
    if (projectedPoints[1].y == projectedPoints[2].y) {
      drawFlatTopTriangle(projectedPoints[1], projectedPoints[2],
                          projectedPoints[0], fillColor);
    } else if (projectedPoints[0].y == projectedPoints[2].y) {
      drawFlatBottomTriangle(projectedPoints[0], projectedPoints[1],
                             projectedPoints[2], fillColor);

    } else {
      vec2_t center = getCenterOfTriangle(projectedPoints);

      drawFlatBottomTriangle(projectedPoints[0], projectedPoints[1], center,
                             fillColor);

      drawFlatTopTriangle(projectedPoints[1], projectedPoints[2], center,
                          fillColor);
    }
  }

  // Draw line between projected points to render triangle edges
  if (renderMode == WIREFRAME || renderMode == WIREFRAME_AND_VERTEX ||
      renderMode == SOLID_WITH_WIREFRAME) {
    drawLine(projectedPoints[0], projectedPoints[1], edgeColor);
    drawLine(projectedPoints[1], projectedPoints[2], edgeColor);
    drawLine(projectedPoints[2], projectedPoints[0], edgeColor);
  }

  if (renderMode == WIREFRAME_AND_VERTEX) {
    int vertexSize = 5;

    drawRect(projectedPoints[0], vertexSize, vertexSize, vertexColor, true);
    drawRect(projectedPoints[1], vertexSize, vertexSize, vertexColor, true);
    drawRect(projectedPoints[2], vertexSize, vertexSize, vertexColor, true);
  }
}

bool shouldCullTriangle(triangle_t triangle) {
  vec3_t a = vec3_sub(triangle.vertices[1], triangle.vertices[0]);
  vec3_t b = vec3_sub(triangle.vertices[2], triangle.vertices[0]);

  vec3_normalize(&a);
  vec3_normalize(&b);

  vec3_t normal = vec3_cross(a, b);

  vec3_normalize(&normal);

  vec3_t cameraRayVec = vec3_sub(cameraPosition, triangle.vertices[0]);

  return vec3_dot(normal, cameraRayVec) <= 0;
}