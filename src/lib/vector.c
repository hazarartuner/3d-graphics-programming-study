//
// Created by Mehmet Hazar Artuner on 29.11.2022.
//

#include "vector.h"

/////////////////////////////////////////////////////
// Vector 2D Functions
/////////////////////////////////////////////////////

float vec2_length(vec2_t vec) { return sqrt(pow(vec.x, 2) + pow(vec.y, 2)); }

vec2_t vec2_add(vec2_t a, vec2_t b) {
  vec2_t result = {a.x + b.x, a.y + b.y};

  return result;
}

vec2_t vec2_sub(vec2_t a, vec2_t b) {
  vec2_t result = {a.x - b.x, a.y - b.y};

  return result;
}

vec2_t vec2_mul(vec2_t vec, float factor) {
  vec2_t result = {vec.x * factor, vec.y * factor};

  return result;
}

vec2_t vec2_div(vec2_t vec, float factor) {
  vec2_t result = {vec.x / factor, vec.y / factor};

  return result;
}

void vec2_normalize(vec2_t* vec) {
  float length = vec2_length(*vec);

  vec->x /= length;
  vec->y /= length;
}

void vec2_sort_by_y(vec2_t* list, int itemCount, bool isAscendingOrder) {
  bool isSorted = false;
  int maxIterationCount = itemCount * itemCount;
  int currenIteration = 0;

  while (!isSorted) {
    isSorted = true;

    if (currenIteration > maxIterationCount) {
      perror("Max iteration count is exceeded in \"vec2_sort_by_y\" function");
      exit(1);
    }

    // Check if sorted
    for (int i = 0; i < itemCount - 1; ++i) {
      if (isAscendingOrder && list[i].y > list[i + 1].y) {
        isSorted = false;
      }

      if (!isAscendingOrder && list[i].y < list[i + 1].y) {
        isSorted = false;
      }

      if (!isSorted) {
        vec2_t temp = list[i];
        list[i] = list[i + 1];
        list[i + 1] = temp;
      }
    }

    currenIteration += 1;
  }
}

vec2_t getCenterOfTriangle(vec2_t* points) {
  // Sort the points desc by Y position
  vec2_sort_by_y(points, 3, true);

  vec2_t center = {};

  center.y = points[1].y;

  center.x = ((points[0].y - points[1].y) * (points[2].x - points[0].x)) /
                 (points[0].y - points[2].y) +
             points[0].x;

  return center;
}

/////////////////////////////////////////////////////
// Vector 3D Functions
/////////////////////////////////////////////////////

float vec3_length(vec3_t vec) {
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

vec3_t vec3_mul(vec3_t vec, float factor) {
  vec3_t result = {vec.x * factor, vec.y * factor, vec.z * factor};

  return result;
}

vec3_t vec3_div(vec3_t vec, float factor) {
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

float vec3_dot(vec3_t a, vec3_t b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

void vec3_normalize(vec3_t* vec) {
  float length = vec3_length(*vec);

  vec->x /= length;
  vec->y /= length;
  vec->z /= length;
}
