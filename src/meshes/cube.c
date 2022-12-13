//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#include "cube.h"

void createCube(triangle_t triangles[]) {
    vec3_t vertices[] = {
        { .x = -1, .y = -1, .z = -1 }, // 1
        { .x = -1, .y =  1, .z = -1 }, // 2
        { .x =  1, .y =  1, .z = -1 }, // 3
        { .x =  1, .y = -1, .z = -1 }, // 4
        { .x =  1, .y =  1, .z =  1 }, // 5
        { .x =  1, .y = -1, .z =  1 }, // 6
        { .x = -1, .y =  1, .z =  1 }, // 7
        { .x = -1, .y = -1, .z =  1 }  // 8
    };

    int triangleIndexes[][3] = {
            // front
        { 0, 1, 2 },
        { 0, 2, 3 },
        // right
        { 3, 2, 4 },
        { 3, 4, 5 },
        // back
        { 5, 4, 6 },
        { 5, 6, 7 },
        // left
        { 7, 6, 1 },
        { 7, 1, 0 },
        // top
        { 1, 6, 4 },
        { 1, 4, 2 },
        // bottom
        { 5, 7, 0 },
        { 5, 0, 3 }
    };

    for (int i = 0; i < 12; i++) {
        triangles[i].vertexA = vertices[triangleIndexes[i][0]];
        triangles[i].vertexB = vertices[triangleIndexes[i][1]];
        triangles[i].vertexC = vertices[triangleIndexes[i][2]];
    }
}

void renderCube(triangle_t triangles[], int triangleCount, uint32_t vertexColor, uint32_t edgeColor) {
  for (int i = 0; i < triangleCount; i++) {
      vec2_t projectedPoints[3];

      projectedPoints[0]= projectAsPerspective(triangles[i].vertexA);
      projectedPoints[1]= projectAsPerspective(triangles[i].vertexB);
      projectedPoints[2]= projectAsPerspective(triangles[i].vertexC);


      drawLine(projectedPoints[0], projectedPoints[1], edgeColor);
      drawLine(projectedPoints[1], projectedPoints[2], edgeColor);
      drawLine(projectedPoints[2], projectedPoints[0], edgeColor);

      for (int j = 0; j < 3; j++) {
        drawRect(
                projectedPoints[j].x,
                projectedPoints[j].y,
                4,
                4,
                vertexColor
        );
      }
  }
}