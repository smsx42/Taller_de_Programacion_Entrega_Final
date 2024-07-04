#include "enemigo.h"

#define PASOS_POR_DIRECCION 15

#define CONFIG Configuracion::config()

Enemigo::Enemigo(uint32_t id_enemigo, uint32_t x, uint32_t y):
        id_enemigo(id_enemigo),
        posicion_x(x),
        posicion_y(y),
        vida(CONFIG.obtenerVidaDefaultEnemigo()),
        esta_quieto(true),
        vivo(true),
        iteraciones_para_revivir(-1),
        pasos_patrullando(0),
        danio(CONFIG.obtener_danio_default_enemigo()),
        tiempo_reaparicion(CONFIG.obtenerTiempoReaparicionEnemigo()),
        direccion_mirando(DERECHA),
        ancho(CONFIG.obtenerAnchoEnemigo()),
        alto(CONFIG.obtenerAltoEnemigo()){
    tiempo_muerte = 0;
    puntos = 0;
    velocidad_x = 3;
    velocidad_y = 0;
    volador = false;
    pos_x_respawn = x;
    pos_y_respawn = y;


    esta_atacando = false;
    tiempo_ataque = -3;
    tiempo_entre_ataque = 3;
}


void Enemigo::recibir_golpe(Bala bala, std::chrono::duration<double> tiempo_transcurrido){
    bala.inflingir_danio(this, tiempo_transcurrido);
}

void Enemigo::recibir_golpe(Personaje *personaje, std::chrono::duration<double> tiempo_transcurrido){
    personaje->inflingir_danio_habilidad(this, tiempo_transcurrido);
}


void Enemigo::recibir_golpe(uint8_t golpe, std::chrono::duration<double> tiempo_transcurrido) {
    vida -= golpe; 
    if(vida <= 0){
        vivo = false;
        vida = 0;
        tiempo_muerte = tiempo_transcurrido.count();
    }
}

void Enemigo::inflingir_danio(Personaje *personaje, std::chrono::duration<double> tiempo_transcurrido){
    if(!esta_atacando){
        esta_atacando = true;
        tiempo_ataque = tiempo_transcurrido.count();
    }
    personaje->recibir_golpe(this->danio,tiempo_transcurrido);
}

//METODO PARA TESTING
void Enemigo::matar(){
    vida = 0;
    vivo = false;
}

void Enemigo::revivir(){
    vida = CONFIG.obtenerVidaDefaultEnemigo();
    vivo = true;
}


bool Enemigo::esta_vivo() { return vivo; }

int Enemigo::obtener_danio() { return danio; }

uint32_t Enemigo::obtener_puntos(){ return puntos; }


uint32_t Enemigo::obtener_posicionX() { return posicion_x; }

uint32_t Enemigo::obtener_posicionY() { return posicion_y; }

uint8_t Enemigo::obtener_vida() { return vida; }

uint8_t Enemigo::obtener_movimiento() { return esta_quieto; }


uint32_t Enemigo::obtener_alto(){
    return alto;
}

uint32_t Enemigo::obtener_ancho(){
    return ancho;
}

bool Enemigo::mirando_izquierda(){
    return direccion_mirando == IZQUIERDA;
}


void Enemigo::actualizar_posicion(std::chrono::duration<double> tiempo_transcurrido, std::map<uint32_t, Objeto*>& map_objetos_solidos) {
    if(!vivo){
        return;
    }

    if(tiempo_transcurrido.count() - tiempo_ataque >= tiempo_entre_ataque){
        esta_atacando = false;
    }
 
    uint32_t nueva_posicion_x = posicion_x + velocidad_x;
    uint32_t nueva_posicion_y = posicion_y + velocidad_y;

    Rectangulo rect_enemigo = {nueva_posicion_x, this->posicion_y, this->ancho, this->alto};

    // Verificar colisión justo debajo del enemigo
    Rectangulo rect_enemigo_abajo = {nueva_posicion_x, this->posicion_y + this->alto, this->ancho, 1};
    // Verificar colisión un poco adelante del enemigo en la dirección en la que se mueve
    Rectangulo rect_enemigo_adelante_abajo;
    if (velocidad_x > 0) {  // Moviéndose a la derecha
        rect_enemigo_adelante_abajo = {nueva_posicion_x + this->ancho, this->posicion_y + this->alto, 1, 1};
    } else {  // Moviéndose a la izquierda
        rect_enemigo_adelante_abajo = {nueva_posicion_x - 1, this->posicion_y + this->alto, 1, 1};
    }

    bool colision_abajo = false;
    bool colision_adelante_abajo = false;

    for (const auto& par_objeto : map_objetos_solidos) {
        Rectangulo rect_objeto = {
            par_objeto.second->obtener_posicionX(), par_objeto.second->obtener_posicionY(),
            par_objeto.second->obtener_ancho(), par_objeto.second->obtener_alto()
        };

        if (rect_enemigo.hay_colision(rect_objeto)) {
            velocidad_x *= -1;
            direccion_mirando = (direccion_mirando == IZQUIERDA) ? DERECHA : IZQUIERDA;
        }

        if (rect_enemigo_abajo.hay_colision(rect_objeto)) {
            colision_abajo = true;
        }

        if (rect_enemigo_adelante_abajo.hay_colision(rect_objeto)) {
            colision_adelante_abajo = true;
        }
    }

    // Si no hay colisión abajo o adelante abajo, cambia de dirección
    if ((!colision_abajo || !colision_adelante_abajo) && !volador) {
        velocidad_x *= -1;
        direccion_mirando = (direccion_mirando == IZQUIERDA) ? DERECHA : IZQUIERDA;
    }

    posicion_x = nueva_posicion_x;
}


Enemigo::~Enemigo() {}
