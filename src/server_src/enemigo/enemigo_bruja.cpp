#include "enemigo_bruja.h"

#define CONFIG Configuracion::config()

Bruja::Bruja(uint32_t id_enemigo, uint32_t x, uint32_t y): Enemigo(id_enemigo,x,y) {
    vida = CONFIG.obtenerVidaBruja();
    puntos = CONFIG.obtenerPuntosBruja();
    danio = CONFIG.obtenerDanioBruja();
    ancho = CONFIG.obtenerAnchoBruja();
    alto = CONFIG.obtenerAltoBruja();
    volador = true;
    velocidad_x = CONFIG.obtenerVelocidadXBruja();
    proba_vida = CONFIG.obtenerProbabilidadVidaBruja();
    proba_municion = CONFIG.obtenerProbabilidadMunicionBruja();
}

uint8_t Bruja::obtener_personaje() {
    return BRUJA;
}

void Bruja::actualizar_posicion(std::chrono::duration<double> tiempo_transcurrido, std::map<uint32_t, Objeto*>& map_objetos_solidos) {
    if(tiempo_transcurrido.count() - tiempo_muerte >= tiempo_reaparicion && !vivo){
        vida = CONFIG.obtenerVidaBruja();
        vivo = true;
        posicion_x = pos_x_respawn;
        posicion_y = pos_y_respawn;
    }
    Enemigo::actualizar_posicion(tiempo_transcurrido, map_objetos_solidos);
}

uint8_t Bruja::obtener_item() {
    int random = std::rand() % 101;
    if(proba_vida[0] <= random && random <= proba_vida[1]){
        return ZANAHORIA;
    }
    return BALA_NORMAL;
}

void Bruja::revivir() {
    vida = CONFIG.obtenerVidaBruja();
    vivo = true;
}