//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#ifndef INC_3DGP_TRANSFORM_H
#define INC_3DGP_TRANSFORM_H

#include "vector.h"

struct Transform {
  vec3_t position;
  vec3_t rotation;
  vec3_t scale;
};

void translate(vec3_t points[], vec3_t translated_points[], int pointCount, struct Transform transform);

#endif //INC_3DGP_TRANSFORM_H
