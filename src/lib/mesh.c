//
// Created by Mehmet Hazar Artuner on 18.12.2022.
//

#include "mesh.h"

mesh_t createMesh(int vertexCount, vec3_t* vertices, int faceCount,
                  face_t* faces) {
  mesh_t mesh = {.vertexCount = vertexCount,
                 .faceCount = faceCount,
                 .vertices = NULL,
                 .faces = NULL,
                 .polygons = NULL,
                 .transformedPolygons = NULL,
                 .position = {0, 0, 0},
                 .rotation = {0, 0, 0}};

  // push vertices to the mesh
  for (int i = 0; i < vertexCount; ++i) {
    vec3_t vertex = vertices[i];
    array_push(mesh.vertices, vertex);
  }

  // create triangle polygons and push to the mesh with faces data.
  for (int i = 0; i < faceCount; ++i) {
    // Create polygon
    triangle_t polygon = {
        .vertexA = vertices[faces[i].a],
        .vertexB = vertices[faces[i].b],
        .vertexC = vertices[faces[i].c],
    };

    array_push(mesh.transformedPolygons, polygon);
    array_push(mesh.polygons, polygon);
    array_push(mesh.faces, faces[i]);
  }

  return mesh;
}

void applyTransform(mesh_t* mesh) {
  for (int i = 0; i < mesh->faceCount; ++i) {
    mesh->transformedPolygons[i] =
        rotateTriangle(mesh->polygons[i], mesh->rotation);
    mesh->transformedPolygons[i] =
        translateTriangle(mesh->transformedPolygons[i], mesh->position);
  }
}