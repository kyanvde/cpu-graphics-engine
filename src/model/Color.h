#ifndef COLOR_H
#define COLOR_H
#include <cstdint>

struct Color {
    uint8_t r, g, b;

    Color() = default;

    Color(const uint8_t r, const uint8_t g, const uint8_t b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

#endif //COLOR_H
