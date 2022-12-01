//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#ifndef INC_3DGP_CUBE_H
#define INC_3DGP_CUBE_H

#include "../lib/vector.h"
#include "../lib/camera.h"
#include "../lib/display.h"
#include "../lib/transform.h"

void createCube(vec3_t* points, dimension_t dimensions, int resolution, struct Transform transform);

void renderCube(vec3_t* points, int pointCount, uint32_t color);

#endif //INC_3DGP_CUBE_H
