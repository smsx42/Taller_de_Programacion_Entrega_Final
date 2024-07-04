#include "objeto_municion.h"



Municion::Municion(uint32_t id_objeto, uint32_t posicion_x, uint32_t posicion_y,
                     double tiempo_reaparicion, uint32_t ancho, uint32_t alto, uint8_t codigo_bala, uint16_t municion):
        Objeto(id_objeto, posicion_x, posicion_y, tiempo_reaparicion, ancho, alto,false),
        codigo_bala(codigo_bala), municion(municion) {
    


}

uint8_t Municion::obtener_objeto() { return codigo_bala; }

void Municion::interactuar_personaje(Personaje* personaje,
                                      std::chrono::duration<double> tiempo_transcurrido) {
    Objeto::interactuar_personaje(personaje,tiempo_transcurrido);
    personaje->agarrar_municion(codigo_bala,municion);
    tiempo_interaccion = tiempo_transcurrido.count();
    mostrar = false;
}
