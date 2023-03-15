cmake_minimum_required(VERSION 3.24)
project(teste)

set(CMAKE_CXX_STANDARD 17)

add_executable(teste main.cpp)

target_link_libraries(teste -lglut -lglfw -lGLEW -lGL -lGLU)
