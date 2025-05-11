#include "display.h"

#include <stdexcept>

namespace luna
{
    Window::Window()
    {
        // TODO: Add fullscreen parameters, window size parameters, window title parameters

        // initializing SDL subsystems...
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            throw std::runtime_error("An error occurred initializing SDL subsystems.");
        }

        // using the SDL to query the resolution of my monitor...
        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(0, &displayMode);

        // ...and setting the resolution
        windowWidth = displayMode.w;
        windowHeight = displayMode.h;

        // initializing an SDL window
        _window = SDL_CreateWindow(
            "Luna Renderer",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_BORDERLESS
        );

        // if the window has not been created...
        if (!_window)
        {
            throw std::runtime_error("An error occurred initializing SDL window.");
        }

        // initializing an SDL renderer
        _renderer = SDL_CreateRenderer(_window, -1, 0);

        // if the renderer has not been created...
        if (!_renderer)
        {
            throw std::runtime_error("An error occurred initializing SDL renderer.");
        }

        // setting the window fullscreen
        SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);

        // allocating memory in color buffer for each pixel of the window
        _colorBuffer.resize(windowWidth * windowHeight);
    }

    Window::~Window()
    {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);

        SDL_DestroyTexture(_colorBufferTexture);

        SDL_Quit();
    }

    void Window::render() const
    {
        translateColorBuffer();

        SDL_RenderPresent(_renderer);
    }

    void Window::translateColorBuffer() const
    {
        // moving color buffer data to the SDL texture
        SDL_UpdateTexture(
            _colorBufferTexture,
            nullptr,
            _colorBuffer.data(),
            static_cast<int>(windowWidth * sizeof(uint32_t))
        );

        // moving SDL texture data to render target (when the render function is called, it'll be rendered)
        SDL_RenderCopy(_renderer, _colorBufferTexture, nullptr, nullptr);
    }
}