cmake_minimum_required(VERSION 3.23)
project(3DGP C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES src/main.c src/display.c src/display.h)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(3D_Graphics_Programming ${SOURCE_FILES})

target_link_libraries(3D_Graphics_Programming ${SDL2_LIBRARIES})
