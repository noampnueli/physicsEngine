cmake_minimum_required(VERSION 3.5)
project(physicsEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lSDL2")

set(SOURCE_FILES main.cpp math_2d.h object.h box.h renderer.cpp renderer.h collisions.h collisions.cpp physics.h constraints.h)
add_executable(physicsEngine ${SOURCE_FILES})