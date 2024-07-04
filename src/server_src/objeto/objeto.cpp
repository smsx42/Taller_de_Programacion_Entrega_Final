#include "objeto.h"


Objeto::Objeto(uint32_t id_objeto, uint32_t posicion_x, uint32_t posicion_y,
               double tiempo_reaparicion, uint32_t ancho, uint32_t alto, bool envenenado):
        id_objeto(id_objeto),
        posicion_x(posicion_x),
        posicion_y(posicion_y),
        tiempo_reaparicion(tiempo_reaparicion),
        tiempo_interaccion(-tiempo_reaparicion),
        mostrar(true),
        ancho(ancho),
        alto(alto), envenenado(envenenado), puede_reaparecer(true) {}

uint32_t Objeto::obtener_id() { return id_objeto; }

uint32_t Objeto::obtener_posicionX() { return posicion_x; }

uint32_t Objeto::obtener_posicionY() { return posicion_y; }

uint32_t Objeto::obtener_ancho() { return ancho; }

uint32_t Objeto::obtener_alto() { return alto; }

bool Objeto::obtener_mostrar() { return mostrar; }

void Objeto::reaparecer(std::chrono::duration<double> tiempo_transcurrido) {
    double tiempo = tiempo_transcurrido.count();
    if (tiempo - tiempo_interaccion >= tiempo_reaparicion && puede_reaparecer) {
        mostrar = true;
    }
}

void Objeto::interactuar_personaje(Personaje* personaje,
                                       std::chrono::duration<double> tiempo_transcurrido){
    
    if(this->envenenado){
        personaje->intoxicarse(tiempo_transcurrido.count());
    }
}

void Objeto::no_reaparecer(){
    puede_reaparecer = false;
}

Objeto::~Objeto() {}
