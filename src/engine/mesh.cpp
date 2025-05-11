#include "mesh.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace luna
{
    std::array<Vector3, cubeVerticesCount> Mesh::_cubeVertices{
        luna::Vector3{ -1, -1, -1 }, // 1
        luna::Vector3{ -1,  1, -1 }, // 2
        luna::Vector3{  1,  1, -1 }, // 3
        luna::Vector3{  1, -1, -1 }, // 4
        luna::Vector3{  1,  1,  1 }, // 5
        luna::Vector3{  1, -1,  1 }, // 6
        luna::Vector3{ -1,  1,  1 }, // 7
        luna::Vector3{ -1, -1,  1 }  // 8
    };

    std::array<Face, cubeFacesCount> Mesh::_cubeFaces{
        // front
        luna::Face{ 1, 2, 3 },
        luna::Face{ 1, 3, 4 },

        // right
        luna::Face{ 4, 3, 5 },
        luna::Face{ 4, 5, 6 },
        
        // back
        luna::Face{ 6, 5, 7 },
        luna::Face{ 6, 7, 8 },
        
        // left
        luna::Face{ 8, 7, 2 },
        luna::Face{ 8, 2, 1 },
        
        // top
        luna::Face{ 2, 7, 5 },
        luna::Face{ 2, 5, 3 },
        
        // bottom
        luna::Face{ 6, 8, 1 },
        luna::Face{ 6, 1, 4 }
    };

    Mesh Mesh::cube()
    {
        Mesh newMesh{};

        // looping through all the cube vertices
        for (size_t i = 0; i < cubeVerticesCount; i++)
        {
            Vector3 vertex = _cubeVertices[1];
            newMesh.vertices.push_back(vertex);
        }

        // looping through all the cube faces
        for (size_t i = 0; i < cubeFacesCount; i++)
        {
            Face face = _cubeFaces[i];
            newMesh.faces.push_back(face);
        }

        return newMesh;
    }

    Mesh Mesh::load(const std::string& filepath)
    {
        Mesh newMesh{};

        // opening the obj file
        std::ifstream objFile(filepath);

        // if something went wrong...
        if (!objFile.is_open())
        {
            // ...we would print an error...
            std::cerr << "Luna: Cannot read the model file." 
                      << "Check the path and ensure that the file exists."
                      << std::endl;

            // ..and quit the program
            exit(-1);
        }

        // a string that contains info whether about a vertex or a face
        std::string currentLine;

        // reading all the strings in the obj file
        while (std::getline(objFile, currentLine))
        {
            // if this is a vertex...
            if (currentLine.rfind("v ", 0) == 0)
            {
                // creating a vertex
                Vector3 vertex;

                // reading the data
                std::stringstream ss(currentLine.substr(2));
                ss >> vertex.x >> vertex.y >> vertex.z;

                newMesh.vertices.push_back(vertex);
            }
            else if (currentLine.rfind("f ", 0) == 0)
            {
                // creating a face
                Face face{0, 0, 0};

                sscanf(
                    currentLine.c_str(),
                    "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
                    &face.a,
                    &face.b,
                    &face.c
                );

                newMesh.faces.push_back(face);
            }
        }

        return newMesh;
    }
}