//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#ifndef INC_3DGP_TRANSFORM_H
#define INC_3DGP_TRANSFORM_H

#include "vector.h"
#include "math.h"
#include "stdbool.h"

struct Transform {
  vec3_t position;
  vec3_t rotation;
  vec3_t scale;
};

vec3_t rotateX(vec3_t point, double rotation);
vec3_t rotateY(vec3_t point, double rotation);
vec3_t rotateZ(vec3_t point, double rotation);

vec3_t rotate(vec3_t point, vec3_t rotation);

vec3_t translate(vec3_t point, vec3_t offset);

#endif //INC_3DGP_TRANSFORM_H
