//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#include "transform.h"

vec3_t rotateX(vec3_t point, double rotation) {
  vec3_t newRotation = {
      .x = point.x, // lock X
      .y = point.y * cos(rotation) + point.z * sin(rotation),
      .z = point.z * cos(rotation) - point.y * sin(rotation),
  };

  return newRotation;
}

vec3_t rotateY(vec3_t point, double rotation) {
  vec3_t newRotation = {
      .x = point.x * cos(rotation) - point.z * sin(rotation),
      .y = point.y, // lock Y
      .z = point.z * cos(rotation) + point.x * sin(rotation),
  };

  return newRotation;
}

vec3_t rotateZ(vec3_t point, double rotation) {
  vec3_t newRotation = {
      .x = point.x * cos(rotation) - point.y * sin(rotation),
      .y = point.y * cos(rotation) + point.x * sin(rotation),
      .z = point.z, // lock Z
  };

  return newRotation;
}

vec3_t rotate(vec3_t point, vec3_t rotation) {
    vec3_t rotatedPoint = rotateX(point, rotation.x);
    rotatedPoint = rotateY(rotatedPoint, rotation.y);
    rotatedPoint = rotateZ(rotatedPoint, rotation.z);

    return rotatedPoint;
}

vec3_t translate(vec3_t point, vec3_t position) {
    point.x += position.x;
    point.y += position.y;
    point.z += position.z;

    return point;
}