#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "engine/mesh.h"
#include "engine/triangle.h"
#include "render/display.h"

namespace application
{
    class App
    {
        /// @brief Path to the model that must be opened
        std::string _pathToModel;

        /// @brief List that stores all the triangles that must be rendered
        std::vector<luna::Triangle> _trianglesToRender;

        /// @brief Represents camera position
        luna::Vector3 _cameraPosition{};

        /// @brief Shows if the game loop should run
        bool _isRunning = false;

        /// @brief The time that the last frame took to be rendered
        int _previousFrameTime{};

        /// @brief Mesh rendered during the app work time
        luna::Mesh _mesh{};

        /// @brief Main window of th application
        std::unique_ptr<luna::Window> _window;

    public:
        /// @brief Creates a new instance of application
        explicit App(std::string pathToModel);

        /// @brief Runs the application and the game loop
        void run();

    private:
        /// @brief Checks any input the user does
        void _processInput();
        /// @brief Updates the states of the different objects in program
        void _update();
        /// @brief Renders the frame
        void _render();
    };
}
