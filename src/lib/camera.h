//
// Created by Mehmet Hazar Artuner on 1.12.2022.
//

#ifndef INC_3DGP_CAMERA_H
#define INC_3DGP_CAMERA_H

#include "vector.h"

extern const float FOV_FACTOR;
extern vec3_t cameraPosition;

vec2_t projectAsOrthographic(vec3_t point);

vec2_t projectAsPerspective(vec3_t point);

#endif //INC_3DGP_CAMERA_H
