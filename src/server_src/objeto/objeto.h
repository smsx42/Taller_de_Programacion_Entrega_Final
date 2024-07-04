#ifndef OBJETO_H_
#define OBJETO_H_

#include <chrono>
#include <cmath>
#include <iostream>

#include "../common_src/accion.h"
#include "../common_src/codigo_objeto.h"

#include "../personaje/personaje.h"



class Personaje;

class Objeto {
protected:
    uint32_t id_objeto;

    uint32_t posicion_x;

    uint32_t posicion_y;

    uint32_t ancho;
    uint32_t alto;

    double tiempo_reaparicion;

    double tiempo_interaccion;

    bool puede_reaparecer;

    bool mostrar;

    bool envenenado;

public:
    Objeto(uint32_t id_objeto, uint32_t posicion_x, uint32_t posicion_y, double tiempo_reaparicion,
           uint32_t ancho, uint32_t alto, bool envenenado);

    // Getters Snapshot

    virtual uint32_t obtener_id();

    virtual uint32_t obtener_posicionX();

    virtual uint32_t obtener_posicionY();

    virtual uint32_t obtener_ancho();

    virtual uint32_t obtener_alto();

    virtual bool obtener_mostrar();

    virtual void reaparecer(std::chrono::duration<double> tiempo_transcurrido);

    virtual ~Objeto();

    // Metodos virtuales para los diferentes objetos

    virtual uint8_t obtener_objeto() = 0;

    virtual void interactuar_personaje(Personaje* personaje,
                                       std::chrono::duration<double> tiempo_transcurrido);

    virtual void no_reaparecer();
};


#endif
