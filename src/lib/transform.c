//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#include "transform.h"

vec3_t rotateX(vec3_t point, float rotation) {
  vec3_t newRotation = {
      .x = point.x, // lock X
      .y = point.y * cos(rotation) + point.z * sin(rotation),
      .z = point.z * cos(rotation) - point.y * sin(rotation),
  };

  return newRotation;
}

vec3_t rotateY(vec3_t point, float rotation) {
  vec3_t newRotation = {
      .x = point.x * cos(rotation) - point.z * sin(rotation),
      .y = point.y, // lock Y
      .z = point.z * cos(rotation) + point.x * sin(rotation),
  };

  return newRotation;
}

vec3_t rotateZ(vec3_t point, float rotation) {
  vec3_t newRotation = {
      .x = point.x * cos(rotation) - point.y * sin(rotation),
      .y = point.y * cos(rotation) + point.x * sin(rotation),
      .z = point.z, // lock Z
  };

  return newRotation;
}

void applyTransform(vec3_t* points, vec3_t* translated_points, int pointCount, struct Transform transform) {

  for (int i = 0; i < pointCount; i++) {
    vec3_t rotatedPoint = rotateX(points[i], transform.rotation.x);
    rotatedPoint = rotateY(rotatedPoint, transform.rotation.y);
    rotatedPoint = rotateZ(rotatedPoint, transform.rotation.z);

    translated_points[i].x = rotatedPoint.x + transform.position.x;
    translated_points[i].y = rotatedPoint.y + transform.position.y;
    translated_points[i].z = rotatedPoint.z + transform.position.z;
  }
}