//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#ifndef INC_3DGP_TRANSFORM_H
#define INC_3DGP_TRANSFORM_H

#include "math.h"
#include "stdbool.h"
#include "triangle.h"
#include "vector.h"

vec3_t rotateX(vec3_t point, float angle);
vec3_t rotateY(vec3_t point, float angle);
vec3_t rotateZ(vec3_t point, float angle);

vec3_t rotate(vec3_t point, vec3_t angle);

vec3_t translate(vec3_t point, vec3_t position);

triangle_t rotateTriangle(triangle_t triangle, vec3_t angle);

triangle_t translateTriangle(triangle_t triangle, vec3_t position);

#endif  // INC_3DGP_TRANSFORM_H
