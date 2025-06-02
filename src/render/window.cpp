#include "window.h"

#include <stdexcept>

namespace luna
{
    Window::Window()
    {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        {
            throw std::runtime_error(SDL_GetError());
        }

        // getting the resolution of the screen
        const SDL_DisplayID displayId = SDL_GetPrimaryDisplay();
        const SDL_DisplayMode* displayMode = SDL_GetCurrentDisplayMode(displayId);

        width = displayMode->w;
        height = displayMode->h;

        // creating a window
        _window = SDL_CreateWindow(
            "Luna Renderer",
            width,
            height,
            SDL_WINDOW_FULLSCREEN
        );

        if (!_window)
        {
            throw std::runtime_error(SDL_GetError());
        }

        // creating a renderer
        _renderer = SDL_CreateRenderer(_window, nullptr);

        if (!_renderer)
        {
            throw std::runtime_error(SDL_GetError());
        }

        // initializing a buffer and a texture
        _colorBuffer.resize(width * height);

        _colorBufferTexture = SDL_CreateTexture(
            _renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            width,
            height
        );

        if (!_colorBufferTexture)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    Window::~Window() noexcept
    {
        if (_colorBufferTexture)
            SDL_DestroyTexture(_colorBufferTexture);

        if (_renderer)
            SDL_DestroyRenderer(_renderer);

        if (_window)
            SDL_DestroyWindow(_window);

        SDL_Quit();
    }

    void Window::render() const noexcept
    {
        _translateColorBuffer();
        SDL_RenderPresent(_renderer);
    }

    int Window::waitUntilNextFrame(const int previousFrameTime) noexcept
    {
        // time that has passed since SDL start
        int current = static_cast<int>(SDL_GetTicks());

        // the time that SDL should wait
        // ReSharper disable once CppTooWideScopeInitStatement
        const int waitTime = previousFrameTime + frameTargetTime - current;

        if (waitTime > 0)
        {
            SDL_Delay(waitTime);
            current = static_cast<Uint32>(SDL_GetTicks());
        }

        return current;
    }

    void Window::_translateColorBuffer() const noexcept
    {
        // putting the color buffer in the SDL texture
        SDL_UpdateTexture(
            _colorBufferTexture,
            nullptr,
            _colorBuffer.data(),
            static_cast<int>(width * sizeof(std::uint32_t))
        );

        SDL_RenderClear(_renderer);
        SDL_RenderTexture(_renderer, _colorBufferTexture, nullptr, nullptr);
    }
}
