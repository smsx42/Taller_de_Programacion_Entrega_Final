#ifndef OBJETO_MUNICION_H_
#define OBJETO_MUNICION_H_

#include <chrono>
#include <cmath>
#include <iostream>

#include "../common_src/accion.h"
#include "../common_src/codigo_objeto.h"
#include "objeto.h"



#define CONFIG Configuracion::config()

class Municion: public Objeto {
private:
    uint8_t codigo_bala;
    uint16_t municion;
public:
    Municion(uint32_t id_objeto, uint32_t posicion_x, uint32_t posicion_y,
              double tiempo_reaparicion, uint32_t ancho, uint32_t alto, uint8_t codigo_bala, uint16_t municion);

    virtual uint8_t obtener_objeto() override;

    virtual void interactuar_personaje(Personaje* personaje,
                                       std::chrono::duration<double> tiempo_transcurrido) override;
};


#endif