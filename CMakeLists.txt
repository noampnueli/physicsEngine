cmake_minimum_required(VERSION 3.5)
project(graphicsTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lSDL2")

set(SOURCE_FILES main.cpp math_2d.cpp math_2d.h object.cpp object.h box.cpp box.h renderer.cpp renderer.h collisions.h)
add_executable(graphicsTest ${SOURCE_FILES})