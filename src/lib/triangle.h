//
// Created by Mehmet Hazar Artuner on 4.12.2022.
//

#ifndef INC_3DGP_TRIANGLE_H
#define INC_3DGP_TRIANGLE_H

#include "vector.h"

typedef struct {
  vec3_t vertices[3];
  uint32_t color;
} triangle_t;

#endif  // INC_3DGP_TRIANGLE_H
