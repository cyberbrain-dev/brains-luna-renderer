cmake_minimum_required(VERSION 3.10)

project(luna-renderer VERSION 0.4.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_definitions(-DLUNA_VERSION="${PROJECT_VERSION}")

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

file(GLOB_RECURSE APP_SRC "src/app/*.cpp")
file(GLOB_RECURSE ENGINE_SRC "src/engine/*.cpp")
file(GLOB_RECURSE RENDER_SRC "src/render/*.cpp")
file(GLOB_RECURSE CORE_SRC   "src/core/*.cpp")

file(GLOB_RECURSE APP_HEADERS "src/app/*.h")
file(GLOB_RECURSE ENGINE_HEADERS "src/engine/*.h")
file(GLOB_RECURSE RENDER_HEADERS "src/render/*.h")
file(GLOB_RECURSE CORE_HEADERS   "src/core/*.h")

add_executable(
    luna-renderer

    ${APP_HEADERS}
    ${ENGINE_HEADERS}
    ${RENDER_HEADERS}
    ${CORE_HEADERS}

    ${APP_SRC}
    ${ENGINE_SRC}
    ${RENDER_SRC}
    ${CORE_SRC}

    src/main.cpp
)

# place a comment here when building, remove when debugging
# target_compile_definitions(luna-renderer PRIVATE LUNA_DEBUG)

set_property(TARGET luna-renderer PROPERTY C_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Wall")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g")


target_link_libraries(luna-renderer ${SDL2_LIBRARIES})
target_link_libraries(luna-renderer m)
