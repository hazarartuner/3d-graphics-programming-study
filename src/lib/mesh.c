//
// Created by Mehmet Hazar Artuner on 18.12.2022.
//

#include "mesh.h"

mesh_t createMesh(int faceCount, int vertexCount, face_t* faces,
                  vec3_t* vertices, vec3_t* normals, vec3_t* texturePositions) {
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
        .vertices =
            {
                vertices[faces[i].vA],
                vertices[faces[i].vB],
                vertices[faces[i].vC],
            },
        .color = faces[i].color,
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

mesh_t loadMesh(char* filePath) {
  vec3_t* vertices = NULL;
  vec3_t* normals = NULL;
  vec3_t* texturePositions = NULL;
  face_t* faces = NULL;

  FILE* fp = fopen(filePath, "r");
  char* line = NULL;
  size_t lineCap = 0;

  if (fp == NULL) {
    perror("File not found");
  }

  // Read each line by line
  while (getline(&line, &lineCap, fp) != -1) {
    // If the line is vertex data
    if (strncmp(line, "v ", 2) == 0) {
      float x, y, z;

      sscanf(line, "v %f %f %f", &x, &y, &z);

      vec3_t vertex = {.x = x, .y = y, .z = z};

      array_push(vertices, vertex);
    }
    // If the line is normal data
    else if (strncmp(line, "vn ", 3) == 0) {
      float x, y, z;

      sscanf(line, "vn %f %f %f", &x, &y, &z);

      vec3_t normal = {.x = x, .y = y, .z = z};

      array_push(normals, normal);
    }
    // If the line is normal data
    else if (strncmp(line, "vt ", 3) == 0) {
      float x, y, z;

      sscanf(line, "vt %f %f %f", &x, &y, &z);

      vec3_t texturePosition = {.x = x, .y = y, .z = z};

      array_push(texturePositions, texturePosition);
    }
    // If the line is face data
    else if (strncmp(line, "f ", 2) == 0) {
      int* vertex_indices = malloc(sizeof(int) * 3);
      int* texture_indices =
          malloc(sizeof(int) * 3);  // @todo: implement it later
      int* normal_indices =
          malloc(sizeof(int) * 3);  // @todo: implement it later

      sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &vertex_indices[0],
             &texture_indices[0], &normal_indices[0], &vertex_indices[1],
             &texture_indices[1], &normal_indices[1], &vertex_indices[2],
             &texture_indices[2], &normal_indices[2]);

      face_t face = {
          .vA = vertex_indices[0] - 1,
          .vB = vertex_indices[1] - 1,
          .vC = vertex_indices[2] - 1,

          .nA = normal_indices[0] - 1,
          .nB = normal_indices[1] - 1,
          .nC = normal_indices[2] - 1,

          .tA = texture_indices[0] - 1,
          .tB = texture_indices[1] - 1,
          .tC = texture_indices[2] - 1,

          // default fill color
          .color = 0xff2587be,
      };

      array_push(faces, face);
    }
  }

  free(line);

  fclose(fp);

  return createMesh(array_length(faces), array_length(vertices), faces,
                    vertices, normals, texturePositions);
}
