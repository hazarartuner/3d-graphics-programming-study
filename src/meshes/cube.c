//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#include "cube.h"

void createCube(vec3_t* points, dimension_t dimension, int resolution, struct Transform transform) {
  int point_index = 0;

  double fixedResolution = (double) (resolution - 1);

  double xStep = dimension.width / fixedResolution;
  double yStep = dimension.height / fixedResolution;
  double zStep = dimension.depth / fixedResolution;
  
  double xHalfLength = dimension.width / 2;
  double yHalfLength = dimension.height / 2;
  double zHalfLength = dimension.depth / 2;

  for (double x=-xHalfLength; x<=xHalfLength; x += xStep) {
    for (double y=-yHalfLength; y<=yHalfLength; y += yStep) {
      for (double z=-zHalfLength; z<=zHalfLength; z += zStep) {
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