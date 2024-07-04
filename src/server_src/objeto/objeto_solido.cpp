#include "objeto_solido.h"

Solido::Solido(uint32_t id_objeto, uint32_t posicion_x, uint32_t posicion_y,
               double tiempo_reaparicion, uint32_t ancho, uint32_t alto, uint8_t tipo_bloque):
        Objeto(id_objeto, posicion_x, posicion_y, tiempo_reaparicion, ancho, alto, false), tipo_bloque(tipo_bloque) {}

uint8_t Solido::obtener_objeto() { return tipo_bloque; }

void Solido::interactuar_personaje(Personaje* personaje,
                                   std::chrono::duration<double> tiempo_transcurrido) {
    // No hace nada
}

uint8_t Solido::obtener_tipo_bloque(){
    return tipo_bloque;
}