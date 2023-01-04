//
// Created by Mehmet Hazar Artuner on 29.11.2022.
//

#include "vector.h"

/////////////////////////////////////////////////////
// Vector 2D Functions
/////////////////////////////////////////////////////

double vec2_length(vec2_t vec) { return sqrt(pow(vec.x, 2) + pow(vec.y, 2)); }

vec2_t vec2_add(vec2_t a, vec2_t b) {
  vec2_t result = {a.x + b.x, a.y + b.y};

  return result;
}

vec2_t vec2_sub(vec2_t a, vec2_t b) {
  vec2_t result = {a.x - b.x, a.y - b.y};

  return result;
}

vec2_t vec2_mul(vec2_t vec, double factor) {
  vec2_t result = {vec.x * factor, vec.y * factor};

  return result;
}

vec2_t vec2_div(vec2_t vec, double factor) {
  vec2_t result = {vec.x / factor, vec.y / factor};

  return result;
}

/////////////////////////////////////////////////////
// Vector 3D Functions
/////////////////////////////////////////////////////

double vec3_length(vec3_t vec) {
  return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

vec3_t vec3_add(vec3_t a, vec3_t b) {
  vec3_t result = {a.x + b.x, a.y + b.y, a.z + b.z};

  return result;
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
  vec3_t result = {a.x - b.x, a.y - b.y, a.z - b.z};

  return result;
}

vec3_t vec3_mul(vec3_t vec, double factor) {
  vec3_t result = {vec.x * factor, vec.y * factor, vec.z * factor};

  return result;
}

vec3_t vec3_div(vec3_t vec, double factor) {
  vec3_t result = {vec.x / factor, vec.y / factor, vec.z / factor};

  return result;
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
  vec3_t result = {
      .x = a.y * b.z - a.z * b.y,
      .y = a.z * b.x - a.x * b.z,
      .z = a.x * b.y - a.y * b.x,
  };

  return result;
}

double vec3_dot(vec3_t a, vec3_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}