//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#include "transform.h"

void translate(vec3_t* points, vec3_t* translated_points, int pointCount, struct Transform transform) {
  for (int i = 0; i < pointCount; i++) {
    translated_points[i].x = points[i].x + transform.position.x;
    translated_points[i].y = points[i].y + transform.position.y;
    translated_points[i].z = points[i].z + transform.position.z;
  }
}