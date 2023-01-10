//
// Created by Mehmet Hazar Artuner on 4.12.2022.
//

#ifndef INC_3DGP_TRIANGLE_H
#define INC_3DGP_TRIANGLE_H

#include "vector.h"

typedef struct {
  vec3_t vertices[3];
  uint32_t color;
  float averageDepth;
} triangle_t;

void sortTrianglesByAverageDepth(triangle_t* triangles, int itemCount,
                                 bool isAscendingOrder);

#endif  // INC_3DGP_TRIANGLE_H
