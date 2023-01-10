//
// Created by Mehmet Hazar Artuner on 18.12.2022.
//

#ifndef INC_3DGP_MESH_H
#define INC_3DGP_MESH_H

#include <regex.h>
#include <string.h>

#include "../lib/transform.h"
#include "../lib/triangle.h"
#include "../lib/vector.h"
#include "../packages/dynamicarray/array.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct {
  // vertex indexes
  int vA;
  int vB;
  int vC;

  // normal indexes
  int nA;
  int nB;
  int nC;

  // texture indexes
  int tA;
  int tB;
  int tC;

  uint32_t color;
} face_t;

typedef struct {
  int vertexCount;
  int faceCount;
  vec3_t* vertices;
  vec3_t* normals;
  vec3_t* texturePositions;
  face_t* faces;
  triangle_t* polygons;
  triangle_t* transformedPolygons;
  vec3_t position;
  vec3_t rotation;
} mesh_t;

mesh_t createMesh(int faceCount, int vertexCount, face_t* faces,
                  vec3_t* vertices, vec3_t* normals, vec3_t* texturePositions);

void applyTransform(mesh_t* mesh);

mesh_t loadMesh(char* filePath);

#endif  // INC_3DGP_MESH_H
