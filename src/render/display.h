#pragma once

#include <SDL2/SDL.h>

#include <cstdint>
#include <vector>

namespace luna
{
    class Window
    {
        friend class Drawer;

    public:
        /// @brief Frame rate of the window
        constexpr int frameRate = 165;
        /// @brief A time span that one frame is presented on the screen
        constexpr float frameTagetTime = 1000.0 / frameRate;

        int windowWidth{};
        int windowHeight{};

    private:
        SDL_Window* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;

        /// @brief An array, representing color buffer - a collection of pixel colors, that should be rendered
        std::vector<uint32_t> _colorBuffer;
        /// @brief A texture that the color buffer is translated to and which is rendered by SDL
        SDL_Texture* _colorBufferTexture = nullptr;

    public:
        /// @brief Creates a simple Luna window
        Window();

        /// @brief Destroys the window and releases all used resources
        ~Window();

        /// @Renders the texture that is now in the rendering target
        void render() const;

    private:
        /// @brief Updates the SDL texture with our color buffer and copies the texture to the rendering target
        void _translateColorBuffer() const;
    };
}