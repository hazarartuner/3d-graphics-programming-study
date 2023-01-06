#ifndef INC_3DGP_VECTOR_H
#define INC_3DGP_VECTOR_H

#include "math.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct {
  float x;
  float y;
} vec2_t;

typedef struct {
  float x;
  float y;
  float z;
} vec3_t;

/////////////////////////////////////////////////////
// Vector 2D Functions
/////////////////////////////////////////////////////
float vec2_length(vec2_t vec);

vec2_t vec2_add(vec2_t a, vec2_t b);

vec2_t vec2_sub(vec2_t a, vec2_t b);

vec2_t vec2_mul(vec2_t vec, float factor);

vec2_t vec2_div(vec2_t vec, float factor);

void vec2_normalize(vec2_t* vec);

void vec2_sort_by_y(vec2_t* list, int itemCount, bool isAscendingOrder);

vec2_t getCenterOfTriangle(vec2_t* points);

/////////////////////////////////////////////////////
// Vector 3D Functions
/////////////////////////////////////////////////////
float vec3_length(vec3_t vec);

vec3_t vec3_add(vec3_t a, vec3_t b);

vec3_t vec3_sub(vec3_t a, vec3_t b);

vec3_t vec3_mul(vec3_t vec, float factor);

vec3_t vec3_div(vec3_t vec, float factor);

vec3_t vec3_cross(vec3_t a, vec3_t b);

float vec3_dot(vec3_t a, vec3_t b);

void vec3_normalize(vec3_t* vec);

#endif  // INC_3DGP_VECTOR_H
