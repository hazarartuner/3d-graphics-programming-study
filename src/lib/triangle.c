//
// Created by Mehmet Hazar Artuner on 4.12.2022.
//

#include "triangle.h"

void sortTrianglesByAverageDepth(triangle_t* triangles, int itemCount,
                                 bool isAscendingOrder) {
  bool isSorted = false;
  int maxIterationCount = itemCount * itemCount;
  int currenIteration = 0;

  while (!isSorted) {
    isSorted = true;

    if (currenIteration > maxIterationCount) {
      perror(
          "Max iteration count is exceeded in \"sortTrianglesByAverageDepth\" "
          "function");
      exit(1);
    }

    // Check if sorted
    for (int i = 0; i < itemCount - 1; ++i) {
      if (isAscendingOrder &&
          triangles[i].averageDepth > triangles[i + 1].averageDepth) {
        isSorted = false;
      }

      if (!isAscendingOrder &&
          triangles[i].averageDepth < triangles[i + 1].averageDepth) {
        isSorted = false;
      }

      if (!isSorted) {
        triangle_t temp = triangles[i];
        triangles[i] = triangles[i + 1];
        triangles[i + 1] = temp;
      }
    }

    currenIteration += 1;
  }
}