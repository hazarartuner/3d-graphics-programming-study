#ifndef INC_3DGP_VECTOR_H
#define INC_3DGP_VECTOR_H

#include "math.h"

typedef struct {
  double x;
  double y;
} vec2_t;

typedef struct {
  double x;
  double y;
  double z;
} vec3_t;

typedef struct {
  int a;
  int b;
  int c;
} face_t;

/////////////////////////////////////////////////////
// Vector 2D Functions
/////////////////////////////////////////////////////
double vec2_length(vec2_t vec);

vec2_t vec2_add(vec2_t a, vec2_t b);

vec2_t vec2_sub(vec2_t a, vec2_t b);

vec2_t vec2_mul(vec2_t vec, double factor);

vec2_t vec2_div(vec2_t vec, double factor);

/////////////////////////////////////////////////////
// Vector 3D Functions
/////////////////////////////////////////////////////
double vec3_length(vec3_t vec);

vec3_t vec3_add(vec3_t a, vec3_t b);

vec3_t vec3_sub(vec3_t a, vec3_t b);

vec3_t vec3_mul(vec3_t vec, double factor);

vec3_t vec3_div(vec3_t vec, double factor);

vec3_t vec3_cross(vec3_t a, vec3_t b);

double vec3_dot(vec3_t a, vec3_t b);

#endif  // INC_3DGP_VECTOR_H
