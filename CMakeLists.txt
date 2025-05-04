cmake_minimum_required(VERSION 3.10)

project(luna-renderer VERSION 0.3.0 LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_definitions(-DLUNA_VERSION="${PROJECT_VERSION}")

add_executable(
    luna-renderer

    
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

# place a comment here when building, remove when debugging
# target_compile_definitions(luna-renderer PRIVATE LUNA_DEBUG)

set_property(TARGET luna-renderer PROPERTY C_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Wall")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g")


target_link_libraries(luna-renderer ${SDL2_LIBRARIES})
target_link_libraries(luna-renderer m)
