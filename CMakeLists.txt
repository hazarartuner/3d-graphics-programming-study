cmake_minimum_required(VERSION 3.23)
project(3DGP C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES src/main.c src/lib/display.c src/lib/display.h src/lib/vector.c src/lib/vector.h src/lib/camera.c src/lib/camera.h src/lib/transform.c src/lib/transform.h src/lib/triangle.c src/lib/triangle.h src/packages/dynamicarray/array.c src/lib/mesh.c src/lib/mesh.h)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(3D_Graphics_Programming ${SOURCE_FILES})

target_link_libraries(3D_Graphics_Programming ${SDL2_LIBRARIES})
