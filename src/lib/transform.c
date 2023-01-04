//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#include "transform.h"

vec3_t rotateX(vec3_t point, double angle) {
  vec3_t newRotation = {
      .x = point.x,  // lock X
      .y = point.y * cos(angle) - point.z * sin(angle),
      .z = point.y * sin(angle) + point.z * cos(angle),
  };

  return newRotation;
}

vec3_t rotateY(vec3_t point, double angle) {
  vec3_t newRotation = {
      .x = point.x * cos(angle) - point.z * sin(angle),
      .y = point.y,  // lock Y
      .z = point.x * sin(angle) + point.z * cos(angle),
  };

  return newRotation;
}

vec3_t rotateZ(vec3_t point, double angle) {
  vec3_t newRotation = {
      .x = point.x * cos(angle) - point.y * sin(angle),
      .y = point.x * sin(angle) + point.y * cos(angle),
      .z = point.z,  // lock Z
  };

  return newRotation;
}

vec3_t rotate(vec3_t point, vec3_t angle) {
  vec3_t rotatedPoint = rotateX(point, angle.x);
  rotatedPoint = rotateY(rotatedPoint, angle.y);
  rotatedPoint = rotateZ(rotatedPoint, angle.z);

  return rotatedPoint;
}

vec3_t translate(vec3_t point, vec3_t position) {
  point.x += position.x;
  point.y += position.y;
  point.z += position.z - 5;

  return point;
}

triangle_t rotateTriangle(triangle_t triangle, vec3_t angle) {
  triangle_t rotatedTriangle = {
      .vertexA = rotate(triangle.vertexA, angle),
      .vertexB = rotate(triangle.vertexB, angle),
      .vertexC = rotate(triangle.vertexC, angle),
  };

  return rotatedTriangle;
}

triangle_t translateTriangle(triangle_t triangle, vec3_t position) {
  triangle_t transformedTriangle = {
      .vertexA = translate(triangle.vertexA, position),
      .vertexB = translate(triangle.vertexB, position),
      .vertexC = translate(triangle.vertexC, position),
  };

  return transformedTriangle;
}