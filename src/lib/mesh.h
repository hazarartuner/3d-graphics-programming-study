//
// Created by Mehmet Hazar Artuner on 18.12.2022.
//

#ifndef INC_3DGP_MESH_H
#define INC_3DGP_MESH_H

#include "../lib/transform.h"
#include "../lib/triangle.h"
#include "../lib/vector.h"
#include "../packages/dynamicarray/array.h"
#include "stdio.h"

typedef struct {
  int vertexCount;
  int faceCount;
  vec3_t* vertices;
  face_t* faces;
  triangle_t* polygons;
  triangle_t* transformedPolygons;
  vec3_t position;
  vec3_t rotation;
} mesh_t;

mesh_t createMesh(int vertexCount, vec3_t* vertices, int faceCount,
                  face_t* faces);

void applyTransform(mesh_t* mesh);

#endif  // INC_3DGP_MESH_H
