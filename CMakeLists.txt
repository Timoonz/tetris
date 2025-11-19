cmake_minimum_required(VERSION 3.5)

project(tp_tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES
    "*.cpp"
    "*.h"
    "imgui/*.cpp"
    "imgui/*.h"
"models/")


add_executable(tp_tetris ${SRC_FILES}
    models/tetrominos.h models/tetrominos.cpp)
include(GNUInstallDirs)

target_include_directories(tp_tetris PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tp_tetris glfw GLEW libGLEW.so libGLU.so libGL.so)
