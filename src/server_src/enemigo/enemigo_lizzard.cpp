#include "enemigo_lizzard.h"
#define CONFIG Configuracion::config()

Lizzard::Lizzard(uint32_t id_enemigo, uint32_t x, uint32_t y): Enemigo(id_enemigo,x,y) {
    vida = CONFIG.obtenerVidaLizzard();
    puntos = CONFIG.obtenerPuntosLizzard();
    danio = CONFIG.obtenerDanioLizzard();
    ancho = CONFIG.obtenerAnchoLizzard();
    alto = CONFIG.obtenerAltoLizzard();
    velocidad_x = CONFIG.obtenerVelocidadXLizzard();
    proba_vida = CONFIG.obtenerProbabilidadVidaLizzard();
    proba_municion = CONFIG.obtenerProbabilidadMunicionLizzard();
}

uint8_t Lizzard::obtener_personaje() {
    return LIZZARD;
}

void Lizzard::actualizar_posicion(std::chrono::duration<double> tiempo_transcurrido, std::map<uint32_t, Objeto*>& map_objetos_solidos) {
    if(tiempo_transcurrido.count() - tiempo_muerte >= tiempo_reaparicion && !vivo){
        vida = CONFIG.obtenerVidaLizzard();
        vivo = true;
        posicion_x = pos_x_respawn;
        posicion_y = pos_y_respawn;
    }
    Enemigo::actualizar_posicion(tiempo_transcurrido, map_objetos_solidos);
}


uint8_t Lizzard::obtener_item() {
    int random = std::rand() % 101;
    if(proba_vida[0] <= random && random <= proba_vida[1]){
        return ZANAHORIA;
    }
    return BALA_NORMAL;
}

void Lizzard::revivir() {
    vida = CONFIG.obtenerVidaLizzard();
    vivo = true;
}