#include "objeto_moneda.h"

#define CONFIG Configuracion::config()


Moneda::Moneda(uint32_t id_objeto, uint32_t posicion_x, uint32_t posicion_y,
                     double tiempo_reaparicion, uint32_t ancho, uint32_t alto, bool envenenado):
        Objeto(id_objeto, posicion_x, posicion_y, tiempo_reaparicion, ancho, alto, envenenado) {
    this->puntos_otorgados = CONFIG.obtenerObjeto(MONEDA).puntos_otorgados;
}

uint8_t Moneda::obtener_objeto() { return MONEDA; }

void Moneda::interactuar_personaje(Personaje* personaje,
                                      std::chrono::duration<double> tiempo_transcurrido) {
    Objeto::interactuar_personaje(personaje,tiempo_transcurrido);
    personaje->asignar_puntos(puntos_otorgados);
    tiempo_interaccion = tiempo_transcurrido.count();
    mostrar = false;
}
