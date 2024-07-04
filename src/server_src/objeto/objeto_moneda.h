#ifndef OBJETO_MONEDA_H_
#define OBJETO_MONEDA_H_

#include <chrono>
#include <cmath>
#include <iostream>

#include "../common_src/accion.h"
#include "objeto.h"

#define ANCHO_MONEDA 25
#define ALTO_MONEDA 25
#define REAPARICION_MONEDA 5

class Moneda: public Objeto {
    uint32_t puntos_otorgados;

public:
    Moneda(uint32_t id_objeto, uint32_t posicion_x, uint32_t posicion_y,
              double tiempo_reaparicion, uint32_t ancho, uint32_t alto, bool envenenado);

    virtual uint8_t obtener_objeto() override;

    virtual void interactuar_personaje(Personaje* personaje,
                                       std::chrono::duration<double> tiempo_transcurrido) override;
};


#endif