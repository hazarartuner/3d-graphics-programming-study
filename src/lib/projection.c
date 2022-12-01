//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#include "projection.h"

vec2_t projectAsOrthographic(vec3_t point) {
  vec2_t projectedPoint = {
          .x = point.x * FOV_FACTOR,
          .y = point.y * FOV_FACTOR
  };

  return projectedPoint;
}

vec2_t projectAsPerspective(vec3_t point) {
  point.x -= cameraPosition.x;
  point.y -= cameraPosition.y;
  point.z -= cameraPosition.z;

  vec2_t projectedPoint = {
          .x = point.x * FOV_FACTOR / point.z,
          .y = point.y * FOV_FACTOR / point.z
  };

  return projectedPoint;
}