//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#include "cube.h"

void createCube(vec3_t* points, dimension_t dimension, int resolution, struct Transform transform) {
  int point_index = 0;

  float fixedResolution = (float) (resolution - 1);

  float xStep = dimension.width / fixedResolution;
  float yStep = dimension.height / fixedResolution;
  float zStep = dimension.depth / fixedResolution;
  
  float xHalfLength = dimension.width / 2;
  float yHalfLength = dimension.height / 2;
  float zHalfLength = dimension.depth / 2;

  for (float x=-xHalfLength; x<=xHalfLength; x += xStep) {
    for (float y=-yHalfLength; y<=yHalfLength; y += yStep) {
      for (float z=-zHalfLength; z<=zHalfLength; z += zStep) {
        vec3_t point = {
          .x = x + transform.position.x,
          .y = y + transform.position.y,
          .z = z + transform.position.z
        };

        points[point_index] = point;

        point_index += 1;
      }
    }
  }
}

void renderCube(vec3_t* points, int pointCount, uint32_t color) {
  for (int i = 0; i < pointCount; i++) {
    vec2_t projectedPoint = projectAsPerspective(points[i]);

    drawRect(
            projectedPoint.x + windowWidth / 2,
            projectedPoint.y + windowHeight / 2,
            4,
            4,
            color
    );
  }
}