cmake_minimum_required(VERSION 3.15)
project(JeraMarchingCubes)

set(CMAKE_CXX_STANDARD 17)

add_executable(JeraMarchingCubes main.cpp jera_marching_cubes.h)
add_executable(CoryBloydMarchingCubes marchingsource.cpp marchingsource_main.cpp marchingsource.h)

add_definitions(-DGL_SILENCE_DEPRECATION)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)

target_link_libraries(CoryBloydMarchingCubes ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

