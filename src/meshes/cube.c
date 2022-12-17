//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#include "cube.h"

triangle_t *createCube() {
  vec3_t vertices[] = {
      {.x = -1, .y = -1, .z = -1},  // 1
      {.x = -1, .y = 1, .z = -1},   // 2
      {.x = 1, .y = 1, .z = -1},    // 3
      {.x = 1, .y = -1, .z = -1},   // 4
      {.x = 1, .y = 1, .z = 1},     // 5
      {.x = 1, .y = -1, .z = 1},    // 6
      {.x = -1, .y = 1, .z = 1},    // 7
      {.x = -1, .y = -1, .z = 1}    // 8
  };

  int triangleIndexes[][3] = {// front
                              {0, 1, 2},
                              {0, 2, 3},
                              // right
                              {3, 2, 4},
                              {3, 4, 5},
                              // back
                              {5, 4, 6},
                              {5, 6, 7},
                              // left
                              {7, 6, 1},
                              {7, 1, 0},
                              // top
                              {1, 6, 4},
                              {1, 4, 2},
                              // bottom
                              {5, 7, 0},
                              {5, 0, 3}};

  triangle_t *mesh = array_hold(NULL, 12, sizeof(triangle_t));

  for (int i = 0; i < 12; i++) {
    mesh[i].vertexA = vertices[triangleIndexes[i][0]];
    mesh[i].vertexB = vertices[triangleIndexes[i][1]];
    mesh[i].vertexC = vertices[triangleIndexes[i][2]];
  }

  return mesh;
}
