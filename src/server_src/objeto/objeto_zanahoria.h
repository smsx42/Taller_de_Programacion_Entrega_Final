#ifndef OBJETO_ZANAHORIA_H_
#define OBJETO_ZANAHORIA_H_

#include <chrono>
#include <cmath>
#include <iostream>

#include "../common_src/accion.h"
#include "objeto.h"

#define ANCHO_ZANAHORIA 25
#define ALTO_ZANAHORIA 25
#define REAPARICION_ZANAHORIA 5

class Zanahoria: public Objeto {
    int vida_restaurada;

public:
    Zanahoria(uint32_t id_objeto, uint32_t posicion_x, uint32_t posicion_y,
              double tiempo_reaparicion, uint32_t ancho, uint32_t alto, bool envenenado);

    virtual uint8_t obtener_objeto() override;

    virtual void interactuar_personaje(Personaje* personaje,
                                       std::chrono::duration<double> tiempo_transcurrido) override;
};


#endif
