#include "personaje.h"
#include "../estado/estado_quieto.h"
#include <random>

#define CONFIG Configuracion::config()

Personaje::Personaje(uint32_t id_jugador, std::vector<SpawnPoint> spawns):
        id_jugador(id_jugador), spawns(spawns), posicion_x(0), posicion_y(0), vida(CONFIG.getVidaPersonaje()), velocidad_x(0), velocidad_y(0), estado(nullptr){
    corriendo = false;
    usando_especial = false;
    saltando = false;
    salto_horizontal = false;
    en_diagonal = false;
    inclinar = false;
    rotacion = IZQUIERDA;
    en_diagonal = false;
    esta_quieto = true;
    esta_disparando = false;
    en_superficie = false;
    muerto = false;
    invulnerable = true;
    intoxicado = false;
    rotacion = 0;
    tiempo_intoxicado = 0;
    tiempo_invulnerable = 0;
    tiempo_salto = 0;
    tiempo_especial = 0;
    puntos = 0;
    bala_actual = BALA_NORMAL;
    municiones[BALA_NORMAL] = -1; // -1 para que sea infinita
    direccion_mirando = DERECHA;
    ancho = CONFIG.getAnchoPersonaje();
    alto = CONFIG.getAltoPersonaje();
    tiempos_recarga[BALA_NORMAL] = -CONFIG.obtenerBala(BALA_NORMAL).tiempo_entre_disparo;
    tiempo_disparo = tiempos_recarga[BALA_NORMAL];

    revivir();
    this->cambiarEstado(new EstadoQuieto());
}

void Personaje::posicion_X(uint32_t x) { this->posicion_x = x; }

void Personaje::posicion_Y(uint32_t y) { this->posicion_y = y; }


void Personaje::mover_derecha(std::chrono::duration<double> tiempo_transcurrido) {
    if(usando_especial)return;

    velocidad_x = corriendo ? CONFIG.getVelocidadXPersonaje() * 2 : CONFIG.getVelocidadXPersonaje();
    esta_quieto = false;
    if(!corriendo){
        this->manejarEstado(ESTADO_CAMINANDO, tiempo_transcurrido);
    }else{
        this->manejarEstado(ESTADO_CORRIENDO, tiempo_transcurrido);
    }

    direccion_mirando = DERECHA;
}

void Personaje::mover_izquierda(std::chrono::duration<double> tiempo_transcurrido) {
    if(usando_especial)return;

    velocidad_x = corriendo ? -CONFIG.getVelocidadXPersonaje() * 2 : -CONFIG.getVelocidadXPersonaje();
    esta_quieto = false;
    if(!corriendo){
        this->manejarEstado(ESTADO_CAMINANDO, tiempo_transcurrido);
    }else{
        this->manejarEstado(ESTADO_CORRIENDO, tiempo_transcurrido);
    }
    direccion_mirando = IZQUIERDA;
}

void Personaje::mover_arriba(std::chrono::duration<double> tiempo_transcurrido) {
    
    if (!saltando && !corriendo) {
        velocidad_y = -CONFIG.getVelocidadYPersonaje();
        esta_quieto = false;
        saltando = true;
        en_superficie = false;
        tiempo_salto = tiempo_transcurrido.count();
        this->manejarEstado(ESTADO_SALTANDO, tiempo_transcurrido);
    }

}

void Personaje::mover_abajo() {
}

uint8_t Personaje::disparar(std::chrono::duration<double> tiempo_transcurrido) {
   double tiempo = tiempo_transcurrido.count();
   if(!usando_especial && !intoxicado && estado->obtener_estado() != ESTADO_HERIDO){
        esta_disparando = true;
        if((tiempo - tiempo_disparo) < CONFIG.obtenerBala(bala_actual).tiempo_entre_disparo) return NINGUNO;
        if(municiones[bala_actual] == -1 ){
            tiempo_disparo = tiempo;
            return bala_actual;
        } else if (municiones[bala_actual] > 0) {
            municiones[bala_actual]--;
            tiempo_disparo = tiempo;
            return bala_actual;
        }
    }
    return NINGUNO;
}

void Personaje::dejar_disparar() { 
    esta_disparando = false; }

void Personaje::quedarse_quieto() {
    velocidad_x = 0;
    corriendo = false;
    esta_quieto = true; //Aca
}

void Personaje::correr_rapido(std::chrono::duration<double> tiempo_transcurrido) { 
    corriendo = saltando ? false : true; 
}

void Personaje::correr() { 
    if(corriendo){
        corriendo = false; 
        if(velocidad_x > 0) velocidad_x = CONFIG.getVelocidadXPersonaje();
        else velocidad_x = -CONFIG.getVelocidadXPersonaje();
    }
}

void Personaje::recibir_golpe(Bala bala, std::chrono::duration<double> tiempo_transcurrido) {
    if(invulnerable) return;
    bala.inflingir_danio(this, tiempo_transcurrido);
}


void Personaje::recibir_golpe(Enemigo *enemigo, std::chrono::duration<double> tiempo_transcurrido){
    if(invulnerable) return;
    enemigo->inflingir_danio(this, tiempo_transcurrido);
}


void Personaje::recibir_golpe(uint8_t golpe, std::chrono::duration<double> tiempo_transcurrido) {
    this->vida -= golpe; 
    if(vida <= 0){
        muerto = true;
        vida = 0;
        velocidad_x = 0;
        velocidad_y = 0;
        this->estado->manejarEstado(ESTADO_MUERTO,tiempo_transcurrido.count());
    } else {
        this->estado->manejarEstado(ESTADO_HERIDO, tiempo_transcurrido.count());
        volverse_invulnerable(tiempo_transcurrido.count());
    }
}

void Personaje::inflingir_danio_bala(Enemigo *enemigo, std::chrono::duration<double> tiempo_transcurrido){
    enemigo->recibir_golpe(CONFIG.obtenerBala(bala_actual).danio, tiempo_transcurrido);
}

void Personaje::inflingir_danio_bala(Personaje *personaje, std::chrono::duration<double> tiempo_transcurrido){
    personaje->recibir_golpe(CONFIG.obtenerBala(bala_actual).danio, tiempo_transcurrido);
}

void Personaje::inflingir_danio_habilidad(Enemigo *enemigo, std::chrono::duration<double> tiempo_transcurrido){
    enemigo->recibir_golpe(obtener_danio_habilidad(), tiempo_transcurrido);
    if(!enemigo->esta_vivo()){
        puntos += enemigo->obtener_puntos();
    }
}

void Personaje::inflingir_danio_habilidad(Personaje *personaje, std::chrono::duration<double> tiempo_transcurrido){
    personaje->recibir_golpe(obtener_danio_habilidad(), tiempo_transcurrido);
}


void Personaje::intoxicarse(double tiempo){
    tiempo_intoxicado = tiempo;
    intoxicado = true;
}

void Personaje::asignar_puntos(uint32_t puntos){
    this->puntos += puntos;
}

void Personaje::curarse(int vida_restaurada){
    vida += vida_restaurada;
    if(vida > CONFIG.getVidaPersonaje()){
        vida = CONFIG.getVidaPersonaje();
    }
}

 void Personaje::cambiar_bala_siguiente() {
    tiempos_recarga[bala_actual] = tiempo_disparo;
    auto it = municiones.find(bala_actual);
        // Buscar el siguiente arma con municiones
    while (true) {
        it++;
        if (it == municiones.end()) {
            it = municiones.begin(); // Volver al principio si llegamos al final
        }
        if (it->second > 0 || it->second == -1) {
            bala_actual = it->first;
            break;
        }
    }

    if (tiempos_recarga.find(bala_actual) != tiempos_recarga.end()) {
        tiempo_disparo = tiempos_recarga[bala_actual];
    } else {
        tiempo_disparo = -CONFIG.obtenerBala(bala_actual).tiempo_entre_disparo;
    }
}

void Personaje::agarrar_municion(uint8_t codigo_municion, int municion){
    municiones[codigo_municion] += municion;
}

void Personaje::revivir(){
    // Aca deberia setearse alguna nueva posicion de spawn
    this->vida = CONFIG.getVidaPersonaje();
    this->muerto = false;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, spawns.size() - 1);

    // Seleccionar un spawn point al azar
    int randomIndex = dis(gen);
    SpawnPoint randomSpawn = spawns[randomIndex];

    posicion_x = randomSpawn.x;
    posicion_y = randomSpawn.y;
}

void Personaje::volverse_invulnerable(double tiempo){
    if(!invulnerable){
        tiempo_invulnerable = tiempo;
        invulnerable = true;
    }
}
void Personaje::volverse_vulnerable(){ //METODO PARA TESTING
    if(invulnerable){
        invulnerable = false;
    }
}

uint8_t Personaje::obtener_puntos_muerte(){
    return CONFIG.getPuntosPersonaje();
}

uint32_t Personaje::obtener_posicionX() { return posicion_x; }

uint32_t Personaje::obtener_posicionY() { return posicion_y; }

uint8_t Personaje::obtener_vida() { return vida; }

uint8_t Personaje::obtener_movimiento() { return esta_quieto; }

uint8_t Personaje::obtener_corriendo() { return corriendo; }

uint8_t Personaje::obtener_habilidad() { return usando_especial; }

uint8_t Personaje::obtener_saltando() { return saltando; }

uint8_t Personaje::obtener_disparando() { return esta_disparando; }

uint8_t Personaje::obtener_danio_habilidad(){ return danio_habilidad; }

uint8_t Personaje::obtener_salto_horizontal(){ return velocidad_x != 0; }

uint8_t Personaje::obtener_rotacion(){ return rotacion;}

uint8_t Personaje::obtener_diagonal(){ return en_diagonal;}

uint8_t Personaje::obtener_estado(){
    return estado->obtener_estado();
}

uint32_t Personaje::obtener_ancho(){
    return ancho;
}

uint32_t Personaje::obtener_alto(){
    return alto;
}

uint8_t Personaje::obtener_intoxicado(){
    return intoxicado;
}

bool Personaje::esta_muerto(){
    return muerto;
}

bool Personaje::es_invulnerable(){
    return invulnerable;
}

uint32_t Personaje::obtener_puntos(){
    return puntos;
}

uint8_t Personaje::obtener_bala_actual(){
    return bala_actual;
}

uint32_t Personaje::obtener_municion_actual(){
    return municiones[bala_actual];
}

bool Personaje::hay_colision(uint32_t pos_x, uint32_t pos_y, uint32_t ancho, uint32_t largo) {
    return (this->posicion_x<pos_x + ancho&& this->posicion_x + this->ancho > pos_x &&
            this->posicion_y<pos_y + largo&& this->posicion_y + this->alto > pos_y);
}

bool Personaje::mirando_izquierda() { return direccion_mirando == IZQUIERDA; }


void Personaje::actualizar_posicion(std::chrono::duration<double> tiempo_transcurrido,
                                    std::map<uint32_t, Objeto*>& map_objetos_solidos, std::map<uint32_t, std::unique_ptr<Objeto>>& map_objetos_comunes) {
    double tiempo_segundos = tiempo_transcurrido.count();
    double delta_tiempo = tiempo_segundos - tiempo_salto;
    salto_horizontal = false;

    if(invulnerable && tiempo_segundos - tiempo_invulnerable >= CONFIG.getTiempoInvulnerabilidad()){
        invulnerable = false;
    }

    if(tiempo_segundos - tiempo_intoxicado >= CONFIG.getTiempoIntoxicacion()){
        intoxicado = false;
    }

    if (tiempo_salto == 0) {
        tiempo_salto = tiempo_segundos;
    }
    
    if (!en_superficie) {
        velocidad_y += CONFIG.getGravedad() * delta_tiempo;
    } else {
        velocidad_y = 0;
    }

    uint32_t nueva_posicion_x = posicion_x + velocidad_x;
    uint32_t nueva_posicion_y = posicion_y + velocidad_y;

    Rectangulo rect_personaje = {nueva_posicion_x, posicion_y,this->ancho, this->alto};
    Rectangulo rect_personaje_arriba = {posicion_x, nueva_posicion_y, this->ancho, this->alto};

    Rectangulo rect_personaje_abajo = {nueva_posicion_x, this->posicion_y + this->alto, this->ancho, 1};
    Rectangulo rect_personaje_adelante_abajo;
    if (velocidad_x >= 0) {  // Moviéndose a la derecha
        rect_personaje_adelante_abajo = {nueva_posicion_x + this->ancho/2, this->posicion_y + this->alto, 1, 1};
    } else if(velocidad_x <= 0){  // Moviéndose a la izquierda
        rect_personaje_adelante_abajo = {nueva_posicion_x - 1, this->posicion_y + this->alto, this->ancho, 1};
    }

    bool colision_abajo = false;
    bool colision_adelante_abajo = false;
    bool colision_suelo = false;

    for (const auto& par_objeto : map_objetos_solidos) {
        Rectangulo rect_objeto = {
            par_objeto.second->obtener_posicionX(), par_objeto.second->obtener_posicionY(),
            par_objeto.second->obtener_ancho(), par_objeto.second->obtener_alto()
        };

        if (par_objeto.second->obtener_mostrar()) {
            if (par_objeto.second->obtener_objeto() == BLOQUE) {
                en_diagonal = false;
                if (rect_personaje_arriba.hay_colision(rect_objeto)) {
                    inclinar = false;
                    if (velocidad_y > 0) {  // Cayendo
                        nueva_posicion_y = rect_objeto.y - this->alto;
                        velocidad_y = 0;
                        saltando = false;
                        colision_suelo = true;
                        tiempo_salto = tiempo_segundos;
                    } else if (velocidad_y < 0) {  // Saltando hacia arriba
                        nueva_posicion_y = rect_objeto.y + rect_objeto.alto;
                        velocidad_y = 0;
                    }
                }
                if (rect_personaje.hay_colision(rect_objeto)) {
                    inclinar = false;
                    corriendo = false;
                    if (velocidad_x > 0) {  // Moviéndose a la derecha
                        nueva_posicion_x = rect_objeto.x - this-> ancho;
                    } else if (velocidad_x < 0) {  // Moviéndose a la izquierda
                        nueva_posicion_x = rect_objeto.x + rect_objeto.ancho;
                    }
                    velocidad_x = 0;
                }
                if (rect_personaje_abajo.hay_colision(rect_objeto)) {
                    colision_abajo = true;
                }

                if (rect_personaje_adelante_abajo.hay_colision(rect_objeto)) {
                    colision_adelante_abajo = true;
                }
            }
            else if(par_objeto.second->obtener_objeto() == TRIANGULO_DERECHO){
                
                uint32_t p1x = this->obtener_posicionX();
                uint32_t p2x = this->obtener_posicionX() + this->obtener_ancho();
                uint32_t x1 = par_objeto.second->obtener_posicionX();
                uint32_t x2 = par_objeto.second->obtener_posicionX() + par_objeto.second->obtener_ancho();
                uint32_t y1 = par_objeto.second->obtener_posicionY();
                uint32_t y2 = par_objeto.second->obtener_posicionY() + par_objeto.second->obtener_alto();
                // Coordenadas y del rectángulo (this)
                uint32_t p1y = this->obtener_posicionY();
                uint32_t p2y = this->obtener_posicionY() + this->obtener_alto();

                uint32_t m = (y2 - y1) / (x2-x1);
                uint32_t b = y1-m*x1;

                if(p1y > y1 && p1y >= y2){ //Estoy por debajo del triangulo
                    continue;
                }
                

                // Verificar si el rectángulo está completamente dentro del triángulo derecho
                if (p1x >= x1 && p1x <= x2 && p2y >= m*p1x + b ) {
                    rotacion = IZQUIERDA;
                    inclinar = true;
                    if(velocidad_y >= 0){
                        saltando = false;
                        nueva_posicion_y = m * nueva_posicion_x + b - this->obtener_alto();
                        colision_suelo = true; // Indica que el personaje está en el suelo después de subir la ramp
                        if (nueva_posicion_x >= x2 && !en_diagonal) {
                            nueva_posicion_y = y2 - this->obtener_alto();
                            en_diagonal = false; // Indicar que se ha salido de la diagonal
                        } else if (nueva_posicion_x <= x1 && !en_diagonal) {
                            nueva_posicion_y = y1 - this->obtener_alto();
                            en_diagonal = false; // Indicar que se ha salido de la diagonal
                        } else {
                            en_diagonal = true;
                        }
                    }
                } else if(p1x <= x1 && x1 <= p2x && y1 <= p2y && p2y <= y2){
                    if (velocidad_x > 0 && velocidad_y == 0) {
                    // Verificar si el personaje está intentando avanzar hacia el triángulo
                        if (nueva_posicion_y + this->ancho != y1) {
                            nueva_posicion_x = x1 - this->obtener_ancho();
                        }
                    }
                }
            } else if(par_objeto.second->obtener_objeto() == TRIANGULO_IZQUIERDO){
                uint32_t p1x = this->obtener_posicionX();
                uint32_t p2x = this->obtener_posicionX() + this->obtener_ancho();
                uint32_t p1y = this->obtener_posicionY();
                uint32_t p2y = this->obtener_posicionY() + this->obtener_alto();
                uint32_t x1 = par_objeto.second->obtener_posicionX();
                uint32_t x2 = par_objeto.second->obtener_posicionX() + par_objeto.second->obtener_ancho();
                uint32_t y1 = par_objeto.second->obtener_posicionY();
                uint32_t y2 = par_objeto.second->obtener_posicionY() + par_objeto.second->obtener_alto();
                

                if(p1y > y1 && p1y >= y2){ //Estoy por debajo del triangulo
                    continue;
                }


                    int b = y1-x1;
                    if(p2x >= x1 && p1y <= p2x + b && p2x <= x2 && p2y >= y1){
                        rotacion = DERECHA;
                        inclinar = true;
                        if(velocidad_y >= 0){
                            saltando = false;
                            nueva_posicion_y = y2 - (p2x - x1) - this->obtener_alto();
                            colision_suelo = true;
                        }
                    } else if(p1x <= x2 && x2 <= p2x && y1 <= p2y && y2>=p2y){
                        if (velocidad_x < 0) {
                            if (nueva_posicion_y + this->ancho != y1) {
                                nueva_posicion_x = x1 + this->obtener_ancho();
                            }
                        }
                    }
            }
        }

    }
    if(saltando){
        en_diagonal = false;
        inclinar = false;
    }


    // Verificar colisiones con objetos comunes
    for (const auto& par_objeto : map_objetos_comunes) {
        par_objeto.second->reaparecer(tiempo_transcurrido);

        Rectangulo rect_objeto = {
            par_objeto.second->obtener_posicionX(), par_objeto.second->obtener_posicionY(),
            par_objeto.second->obtener_ancho(), par_objeto.second->obtener_alto()
        };

        if (par_objeto.second->obtener_mostrar()) {
            if (rect_personaje.hay_colision(rect_objeto) || rect_personaje_arriba.hay_colision(rect_objeto)) {
                par_objeto.second->interactuar_personaje(this, tiempo_transcurrido);
            }
        }
    }

    if (!saltando && velocidad_x == 0 && esta_quieto) {
        this->manejarEstado(ESTADO_QUIETO, tiempo_transcurrido);
    }

    if ((!colision_abajo || !colision_adelante_abajo) && !saltando && !esta_disparando && esta_quieto && !inclinar) {
        this->manejarEstado(ESTADO_TAMBALEAR, tiempo_transcurrido);
    }


    if(saltando and velocidad_x != 0){
        salto_horizontal = true;
    }

    if (velocidad_x != 0 && !saltando) {
        if (!corriendo) this->manejarEstado(ESTADO_CAMINANDO, tiempo_transcurrido);
    }
    
    if(velocidad_y > 0){
        this->manejarEstado(ESTADO_CAYENDO, tiempo_transcurrido);
    }
    

    posicion_x = nueva_posicion_x;
    posicion_y = nueva_posicion_y;

    this->actualizar(tiempo_transcurrido.count());

    if (posicion_y > CONFIG.getAltoPantalla() - CONFIG.getAltoPersonaje()) {  // Si hay colision abajo
        posicion_y = CONFIG.getAltoPantalla() - CONFIG.getAltoPersonaje();
        saltando = false;
        colision_suelo = true;
        tiempo_salto = tiempo_segundos;
    } else if(posicion_y <= 0){
        posicion_y = 1;
    }

    en_superficie = colision_suelo;
}



void Personaje::cambiarEstado(Estado *estado){
    if (this->estado != nullptr){
        delete this->estado;
    }
    this->estado = estado;
    this->estado->asignarPersonaje(this);
}

void Personaje::manejarEstado(uint8_t codigo_estado, std::chrono::duration<double> tiempo_transcurrido){
    this->estado->manejarEstado(codigo_estado, tiempo_transcurrido.count());
}

void Personaje::actualizar(double tiempo){
    this->estado->actualizar(tiempo);
}


Personaje::~Personaje() {
    delete estado;
}




