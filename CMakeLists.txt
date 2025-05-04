cmake_minimum_required(VERSION 3.10)

project(brains-luna-renderer LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(
    brains-luna-renderer

    
    
    src/display.h
    src/display.c

    src/draw.h
    src/draw.c

    src/list.h
    src/list.c

    src/mesh.h
    src/mesh.c

    src/project.h
    src/project.c

    src/triangle.h
    src/triangle.c
    
    src/vector.h
    src/vector.c
    
    src/main.c
)

set_property(TARGET brains-luna-renderer PROPERTY C_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Wall")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g")


target_link_libraries(brains-luna-renderer ${SDL2_LIBRARIES})
target_link_libraries(brains-luna-renderer m)
