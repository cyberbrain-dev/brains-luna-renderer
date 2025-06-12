#pragma once

#include <memory>
#include <string>
#include <vector>

#include "engine/mesh.h"
#include "engine/triangle.h"

#include "render/window.h"
#include "render/drawer.h"

namespace application
{
    /// @brief Represents LunaRenderer application
    class App
    {
        const luna::Color _fillTriangleColor{159, 160, 195, 255};
        const luna::Color _wireframeTriangleColor{188, 248, 236, 255};

        /// @brief List that stores all the triangles that must be rendered
        std::vector<luna::Triangle> _trianglesToRender;

        /// @brief Represents camera position
        luna::Vector3 _cameraPosition{};

        /// @brief Shows if the game loop should run
        bool _isRunning = false;

        /// @brief The time that the last frame took to be rendered
        int _previousFrameTime{};

        /// @brief Main window of the application
        std::unique_ptr<luna::Window> _window;

        /// @brief An object for drawing objects on the window
        luna::Drawer _drawer;

        /// @brief Mesh rendered during the app work time
        luna::Mesh _mesh{};
    public:
        /// @brief Creates a new instance of application
        /// @param pathToModel A path to an obj-file
        /// that the application has to render
        /// @throw std::runtime_error if the window failed initialization or if the mesh failed loading
        explicit App(const std::string& pathToModel);

        /// @brief Runs the application and the game loop
        void run();

    private:
        /// @brief Checks any input the user does
        void _processInput() noexcept;
        /// @brief Updates the states of the different objects in program
        void _update() noexcept;
        /// @brief Renders the frame
        void _render() noexcept;
    };
}
