#include "enemigo_rat.h"
#define CONFIG Configuracion::config()


Rat::Rat(uint32_t id_enemigo, uint32_t x, uint32_t y): Enemigo(id_enemigo,x,y) {
    vida = CONFIG.obtenerVidaRat();
    puntos = CONFIG.obtenerPuntosRat();
    danio = CONFIG.obtenerDanioRat();
    ancho = CONFIG.obtenerAnchoRat();
    alto = CONFIG.obtenerAltoRat();
    velocidad_x = CONFIG.obtenerVelocidadXRat();
    proba_vida = CONFIG.obtenerProbabilidadVidaRat();
    proba_municion = CONFIG.obtenerProbabilidadMunicionRat();
}

uint8_t Rat::obtener_personaje() {
    return RAT;
}

void Rat::actualizar_posicion(std::chrono::duration<double> tiempo_transcurrido, std::map<uint32_t, Objeto*>& map_objetos_solidos) {
    if(tiempo_transcurrido.count() - tiempo_muerte >= tiempo_reaparicion && !vivo){
        vida = CONFIG.obtenerVidaRat();
        vivo = true;
        posicion_x = pos_x_respawn;
        posicion_y = pos_y_respawn;
    }
    Enemigo::actualizar_posicion(tiempo_transcurrido, map_objetos_solidos);
}

uint8_t Rat::obtener_item() {
    int random = std::rand() % 101;
    if(proba_vida[0] <= random && random <= proba_vida[1]){
        return ZANAHORIA;
    }
    return BALA_NORMAL;
}

void Rat::revivir() {
    vida = CONFIG.obtenerVidaRat();
    vivo = true;

}