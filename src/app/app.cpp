#include "app.h"

#include <SDL2/SDL.h>

#include <array>

#include "render/drawer.h"

namespace application
{
    App::App(const std::string& pathToModel)
        : _window(std::make_unique<luna::Window>()),
          _drawer(*_window),
          _mesh(luna::Mesh::load(pathToModel)) {}

    void App::run()
    {
        _isRunning = true;

        while (_isRunning)
        {
            _processInput();
            _update();
            _render();
        }
    }

    void App::_processInput() noexcept
    {
        // Creating and polling the current moment event
        SDL_Event currentEvent;
        SDL_PollEvent(&currentEvent);

        // Determining the type of the event
        switch (currentEvent.type)
        {
            case SDL_EVENT_QUIT:
                _isRunning = false;
                break;

            case SDL_EVENT_KEY_DOWN:
                if (currentEvent.key.key == SDLK_ESCAPE)
                    _isRunning = false;
                break;

            default:
                break;
        }
    }

    void App::_update() noexcept
    {
        // waiting till this frame must be updated
        _previousFrameTime = luna::Window::waitUntilNextFrame(_previousFrameTime);

        _mesh.rotation.x += 0.005;
        _mesh.rotation.y += 0.005;
        _mesh.rotation.z += 0.005;

        // looping through all the faces of the mesh
        for (const luna::Face& currentFace : _mesh.faces)
        {
            // getting vertices of current face
            std::array<luna::Vector3, 3> currentFaceVertices{
                _mesh.vertices[currentFace.a - 1],
                _mesh.vertices[currentFace.b - 1],
                _mesh.vertices[currentFace.c - 1]
            };

            // a little array that'll help us to save the transformed vertices
            std::array<luna::Vector3, 3> transformedVertices;

            // looping through all three vertices of this current face to apply transformations
            for (size_t i = 0; i < 3; i++)
            {
                // getting the vertex of current face that is NOT transformed yet
                luna::Vector3 transformedVertex = currentFaceVertices[i];

                // applying the rotation
                transformedVertex = transformedVertex.rotate(_mesh.rotation);

                // moving the vertex a bit "inside" the monitor
                transformedVertex.z += 5;

                // saving the vertex
                transformedVertices[i] = transformedVertex;
            }

            // getting the points of the triangle which is or is not going to be rendered (backface culling will decide)
            auto a = transformedVertices[0];   /*   a   */
            auto b = transformedVertices[1];   /*  / \  */
            auto c = transformedVertices[2];   /* c---b */

            // getting two vectors of the face to find the cross product (face normal)
            auto ab = b - a;
            auto ac = c - a;

            // computing the face normal
            auto normal = luna::Vector3::cross(ab, ac);
            normal.normalize();

            // finding the vector between a point in the triangle and the camera origin
            // ReSharper disable once CppTooWideScopeInitStatement
            auto cameraRay = _cameraPosition - a;

            // bypass the triangle if it is looking away from the camera
            if (luna::Vector3::dot(normal, cameraRay) < 0)
                continue;

            // a little array that'll help us to save the projected vertices
            std::array<luna::Vector2, 3> projectedVertices;

            // looping through all three vertices to perform projection
            // and to save those projected points in the triangle
            for (size_t i = 0; i < 3; i++)
            {
                // projecting the transformed point
                luna::Vector2 projectedVertex = transformedVertices[i].projectPerspective(640); // 128 for orth

                // scale and translating projected points to the middle of the screen
                projectedVertex.x += static_cast<float>(_window->width) / 2;
                projectedVertex.y += static_cast<float>(_window->height) / 2;

                // saving our projected point
                projectedVertices[i] = projectedVertex;
            }

            // creating a triangle that is going to be rendered...
            luna::Triangle triangle{
                projectedVertices[0],
                projectedVertices[1],
                projectedVertices[2],
            };

            // ...and pushing it to the vector of triangles
            _trianglesToRender.push_back(triangle);
        }
    }

    void App::_render() noexcept
    {
        _drawer.drawDottedGrid(10, 10, luna::colorGrey);

        // drawing triangles
        for (const luna::Triangle& triangle : _trianglesToRender)
        {
            _drawer.drawEmptyTriangle(triangle, luna::colorWhite);
            _drawer.drawFilledTriangle(triangle, fillTriangleColor);
        }

        // rendering all the stuff drawn
        _window->render();

        // deleting all the triangles as they are already drawn
        _trianglesToRender.clear();

        // "clearing" the color buffer
        _drawer.fill(luna::colorBlack);
    }
}
