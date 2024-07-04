#include "enemigo_fencer.h"

#define CONFIG Configuracion::config()

Fencer::Fencer(uint32_t id_enemigo, uint32_t x, uint32_t y): Enemigo(id_enemigo,x,y) {
    vida = CONFIG.obtenerVidaFencer();
    puntos = CONFIG.obtenerPuntosFencer();
    danio = CONFIG.obtenerDanioFencer();
    ancho = CONFIG.obtenerAnchoFencer();
    alto = CONFIG.obtenerAltoFencer();
    velocidad_x = CONFIG.obtenerVelocidadXFencer();
    proba_vida = CONFIG.obtenerProbabilidadVidaFencer();
    proba_municion = CONFIG.obtenerProbabilidadMunicionFencer();
}

uint8_t Fencer::obtener_personaje() {
    return FENCER;
}


void Fencer::actualizar_posicion(std::chrono::duration<double> tiempo_transcurrido, std::map<uint32_t, Objeto*>& map_objetos_solidos) {
    if(tiempo_transcurrido.count() - tiempo_muerte >= tiempo_reaparicion && !vivo){
        vida = CONFIG.obtenerVidaFencer();
        vivo = true;
        posicion_x = pos_x_respawn;
        posicion_y = pos_y_respawn;
    }
    Enemigo::actualizar_posicion(tiempo_transcurrido, map_objetos_solidos);
}

uint8_t Fencer::obtener_item() {
    int random = std::rand() % 101;
    if(proba_vida[0] <= random && random <= proba_vida[1]){
        return ZANAHORIA;
    }
    return BALA_NORMAL;
}

void Fencer::revivir() {
    vida = CONFIG.obtenerVidaFencer();
    vivo = true;
}