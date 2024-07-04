#ifndef SERVER_RECTANGULO_H_
#define SERVER_RECTANGULO_H_

#include <iostream>

class Rectangulo {
public:
    uint32_t x, y, ancho, alto;

    Rectangulo(){}

    Rectangulo(uint32_t x, uint32_t y, uint32_t ancho, uint32_t alto):
            x(x), y(y), ancho(ancho), alto(alto) {}

    bool hay_colision(const Rectangulo& otro) const {
        return (this->x<otro.x + otro.ancho&& this->x + this->ancho> otro.x &&
                this->y<otro.y + otro.alto&& this->y + this->alto> otro.y);
    }


    // Detección de colisión en el eje X (horizontal)
    bool hay_colision_x(const Rectangulo& otro) const {
        return (this->x<otro.x + otro.ancho&& this->x + this->ancho> otro.x);
    }

    // Detección de colisión en el eje Y (vertical)
    bool hay_colision_y(const Rectangulo& otro) const {
        return (this->y<otro.y + otro.alto&& this->y + this->alto> otro.y);
    }



    bool hay_colision_triangular_derecho(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) const {
        // Coordenadas del punto del personaje
        uint32_t px = this->x;
        uint32_t py = this->y + this->alto; // Y se ajusta para estar en el fondo del personaje

        // Verificar si el punto (px, py) está dentro del triángulo derecho
        // Calcular la pendiente m de la recta inclinada
        uint32_t m = (y2 - y1) / (x2 - x1);

        // Calcular el término independiente b de la recta inclinada
        uint32_t b = y1 - m * x1;

        // Calcular la posición en y de la recta en la coordenada x del punto del personaje
        uint32_t recta_y = m * px + b;

        // Verificar si el punto del personaje está arriba de la recta inclinada y dentro de los límites del triángulo derecho
        if (py <= recta_y && px >= x1 && px <= x2 && py >= y1 && py <= y2) {
            return true; // Hay colisión con el triángulo derecho
        }

    return false; // No hay colisión
}

};




#endif
