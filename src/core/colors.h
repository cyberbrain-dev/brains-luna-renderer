#pragma once

#include <cstdint>

namespace luna
{
    /// @brief Represents a color in RGBA-format
    struct Color
    {
        uint8_t r{}, g{}, b{}, a{};

        /// @brief Creates zero RGBA-color (0, 0, 0, 0)
        constexpr Color() noexcept = default;
        /// @brief Creates a color
        /// @param r amount of red
        /// @param g amount of green
        /// @param b amount of blue
        /// @param a transparency (the lower the value is, the more transparent color is)
        constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept
            : r{r}, g{g}, b{b}, a{a} {}

        /// @brief Converts `luna::Color` into a `luna::Color`
        /// @return A `luna::Color` that represents the RGBA-color
        constexpr uint32_t toUint32() const noexcept
        {
            return (uint32_t(a) << 24) | (uint32_t(r) << 16) | (uint32_t(g) << 8) | uint32_t(b);
        }
    };

    constexpr Color colorBlack    {  0,   0,   0, 255}; // 0xFF000000
    constexpr Color colorRed      {  0, 255,   0, 255}; // 0xFFFF0000
    constexpr Color colorGreen    {  0,   0, 255, 255}; // 0xFF00FF00
    constexpr Color colorBlue     {255,   0,   0, 255}; // 0xFF0000FF
    constexpr Color colorYellow   {  0, 255, 255, 255}; // 0xFFFFFF00
    constexpr Color colorPurple   {255, 255,   0, 255}; // 0xFFFF00FF
    constexpr Color colorCyan     {255,   0, 255, 255}; // 0xFF00FFFF
    constexpr Color colorGrey     { 85,  85,  85, 255}; // 0xFF555555
    constexpr Color colorWhite    {255, 255, 255, 255}; // 0xFFFFFFFF
}


// #define LUNA_COLOR_BLACK        0xFF000000
// #define LUNA_COLOR_WHITE        0xFFFFFFFF

// #define LUNA_COLOR_RED          0xFFFF0000
// #define LUNA_COLOR_GREEN        0xFF00FF00
// #define LUNA_COLOR_BLUE         0xFF0000FF

// #define LUNA_COLOR_YELLOW       0xFFFFFF00
// #define LUNA_COLOR_PURPLE       0xFFFF00FF
// #define LUNA_COLOR_CYAN         0xFF00FFFF

// #define LUNA_COLOR_GREY         0xFF555555