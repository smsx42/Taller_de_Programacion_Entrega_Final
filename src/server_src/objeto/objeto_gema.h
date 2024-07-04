#ifndef OBJETO_GEMA_H_
#define OBJETO_GEMA_H_

#include <chrono>
#include <cmath>
#include <iostream>

#include "objeto.h"

#define ANCHO_GEMA 25
#define ALTO_GEMA 25
#define REAPARICION_GEMA 5

class Gema: public Objeto {
    uint32_t puntos_otorgados;

public:
    Gema(uint32_t id_objeto, uint32_t posicion_x, uint32_t posicion_y,
              double tiempo_reaparicion, uint32_t ancho, uint32_t alto, bool envenenado);

    virtual uint8_t obtener_objeto() override;

    virtual void interactuar_personaje(Personaje* personaje,
                                       std::chrono::duration<double> tiempo_transcurrido) override;
};


#endif