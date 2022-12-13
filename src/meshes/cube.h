//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#ifndef INC_3DGP_CUBE_H
#define INC_3DGP_CUBE_H

#include "../lib/vector.h"
#include "../lib/camera.h"
#include "../lib/display.h"
#include "../lib/transform.h"
#include "../lib/triangle.h"

void createCube(triangle_t triangles[]);

void renderCube(triangle_t triangles[], int triangleCount, uint32_t vertexColor, uint32_t edgeColor);

#endif //INC_3DGP_CUBE_H
