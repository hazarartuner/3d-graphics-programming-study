cmake_minimum_required(VERSION 3.23)
project(Temp C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(3D_Graphics_Programming src/main.c)
target_link_libraries(3D_Graphics_Programming ${SDL2_LIBRARIES})
