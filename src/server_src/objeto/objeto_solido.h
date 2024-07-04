#ifndef OBJETO_SOLIDO_H_
#define OBJETO_SOLIDO_H_

#include <chrono>
#include <cmath>
#include <iostream>

#include "../common_src/accion.h"

#include "objeto.h"

class Solido: public Objeto {
private:
       uint8_t tipo_bloque;

public:
    Solido(uint32_t id_objeto, uint32_t posicion_x, uint32_t posicion_y, double tiempo_reaparicion,
           uint32_t ancho, uint32_t alto, uint8_t tipo_bloque);

       virtual uint8_t obtener_objeto() override;

       virtual void interactuar_personaje(Personaje* personaje,
                                       std::chrono::duration<double> tiempo_transcurrido) override;

       uint8_t obtener_tipo_bloque();
};


#endif
