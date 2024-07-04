#include "objeto_zanahoria.h"

#define CONFIG Configuracion::config()


Zanahoria::Zanahoria(uint32_t id_objeto, uint32_t posicion_x, uint32_t posicion_y,
                     double tiempo_reaparicion, uint32_t ancho, uint32_t alto, bool envenenado):
        Objeto(id_objeto, posicion_x, posicion_y, tiempo_reaparicion, ancho, alto, envenenado) {
    this->vida_restaurada = CONFIG.obtenerObjeto(ZANAHORIA).vida_restaurada;
}

uint8_t Zanahoria::obtener_objeto() { return ZANAHORIA; }

void Zanahoria::interactuar_personaje(Personaje* personaje,
                                      std::chrono::duration<double> tiempo_transcurrido) {
    Objeto::interactuar_personaje(personaje,tiempo_transcurrido);
    personaje->curarse(vida_restaurada);
    tiempo_interaccion = tiempo_transcurrido.count();
    mostrar = false;
}
