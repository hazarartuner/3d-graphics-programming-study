//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#include "camera.h"

#include "display.h"

const float FOV_FACTOR = 512;
vec3_t cameraPosition = {.x = 0, .y = 0, .z = -2};

vec2_t projectAsOrthographic(vec3_t point) {
  vec2_t projectedPoint = {.x = point.x * FOV_FACTOR,
                           .y = point.y * FOV_FACTOR};

  return projectedPoint;
}

vec2_t projectAsPerspective(vec3_t point) {
  point.x -= cameraPosition.x;
  point.y -= cameraPosition.y;
  point.z -= cameraPosition.z;

  vec2_t projectedPoint;

  projectedPoint.x = (point.x / (1 + point.z)) * FOV_FACTOR + (windowWidth / 2);
  projectedPoint.y =
      (point.y / (1 + point.z)) * FOV_FACTOR + (windowHeight / 2);

  return projectedPoint;
}