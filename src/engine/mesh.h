#pragma once

#include <array>
#include <string>
#include <vector>

#include "engine/triangle.h"
#include "engine/vector.h"

namespace luna
{
    constexpr size_t cubeVerticesCount = 8;
    constexpr size_t cubeFacesCount = 12;

    /// @brief Represents a 3D-mesh
    struct Mesh
    {
        /// @brief dynamic vector of 3D-vectors
        std::vector<Vector3> vertices;
        /// @brief dynamic vector of faces
        std::vector<Face> faces;
        /// @brief mesh's rotation
        Vector3 rotation{};


        /// @brief Creates a mesh
        Mesh() = default;


        /// @brief Creates a simple cube mesh
        static Mesh cube();

        /// @brief Loads a mesh from the OBJ file
        /// @param filepath a path to the file
        static Mesh load(const std::string &filepath);

    private:
        /// @brief An array of cube vertices
        static std::array<Vector3, cubeVerticesCount> cubeVertices;
        /// @brief An array of cube faces
        static std::array<Face, cubeFacesCount> cubeFaces;
    };
}