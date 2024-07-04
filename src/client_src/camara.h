#ifndef CAMARA_H
#define CAMARA_H

#include "SDL2pp/SDL2pp.hh"

class Camara {
private:
    SDL2pp::Rect camara;

public:
    explicit Camara(int x_inicial, int y_inicial, int ancho, int alto);

    void actualizar_posicion(int x, int y);

    int obtener_posicion_x();

    int obtener_posicion_y();

    void definir_posicion_x(int x);

    void definir_posicion_y(int y);
};

#endif 