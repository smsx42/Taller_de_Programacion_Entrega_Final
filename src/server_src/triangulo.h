#ifndef SERVER_TRIANGULO_H_
#define SERVER_TRIANGULO_H_

#include <iostream>

class Triangulo {
public:
    // Método estático para determinar si un punto pt está dentro del triángulo formado por v1, v2, v3
    static bool pointInTriangle(uint32_t ptX, uint32_t ptY, uint32_t v1X, uint32_t v1Y, uint32_t v2X, uint32_t v2Y, uint32_t v3X, uint32_t v3Y) {
        auto sign = [](uint32_t p1x, uint32_t p1y, uint32_t p2x, uint32_t p2y, uint32_t p3x, uint32_t p3y) {
            return (p1x - p3x) * (p2y - p3y) - (p2x - p3x) * (p1y - p3y);
        };

        bool b1, b2, b3;
        b1 = sign(ptX, ptY, v1X, v1Y, v2X, v2Y) < 0.0;
        b2 = sign(ptX, ptY, v2X, v2Y, v3X, v3Y) < 0.0;
        b3 = sign(ptX, ptY, v3X, v3Y, v1X, v1Y) < 0.0;

        return ((b1 == b2) && (b2 == b3));
    }
};

#endif // SERVER_TRIANGULO_H_
