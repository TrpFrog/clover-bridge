cmake_minimum_required(VERSION 3.20)
project(clover-bridge)

set(CMAKE_CXX_STANDARD 17)
set(sources
        src/main.cpp
        src/parts.cpp
        src/parts.h
        src/draw.cpp
        src/draw.h
        src/camera.cpp
        src/camera.h
        src/useful_macros.h
)

add_executable(clover-bridge ${sources})

target_link_libraries(clover-bridge "-framework GLUT")
target_link_libraries(clover-bridge "-framework OpenGL")