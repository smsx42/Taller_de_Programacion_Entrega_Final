#ifndef SERVER_ENEMIGO_H_
#define SERVER_ENEMIGO_H_

#include <chrono>
#include <cmath>
#include <iostream>

#include "../common_src/accion.h"
#include "../common_src/codigo_enemigo.h"
#include "../configuracion.h"
#include "../personaje/personaje.h"
#include "../bala/bala.h"


class Personaje;
class Bala;
class Objeto;

#define WIDTH 640
#define HEIGHT 480

class Enemigo {
protected:
    uint32_t id_enemigo;  // EL ATRIBUTO ID PROBABLEMENTE HAYA QUE REMOVERLO
    uint32_t posicion_x;
    uint32_t posicion_y;
    int vida;
    uint32_t puntos;
    bool esta_quieto;
    bool volador;
    bool esta_atacando;
    double tiempo_ataque;
    double tiempo_entre_ataque;
    uint32_t ancho;
    uint32_t alto;
    uint32_t pos_x_respawn;
    uint32_t pos_y_respawn;
    std::vector<int> proba_vida;
    std::vector<int> proba_municion;


    double velocidad_x;
    double velocidad_y;
    double tiempo_muerte;
    double tiempo_reaparicion;
    uint8_t direccion_mirando;
    bool vivo;
    int iteraciones_para_revivir;

    int pasos_patrullando;
    int danio;

public:
    explicit Enemigo(uint32_t id_enemigo, uint32_t x, uint32_t y);

    // Acciones

    virtual bool esta_vivo();

    virtual void recibir_golpe(uint8_t golpe, std::chrono::duration<double> tiempo_transcurrido);
    
    virtual void recibir_golpe(Bala bala, std::chrono::duration<double> tiempo_transcurrido);

    virtual void recibir_golpe(Personaje *personaje, std::chrono::duration<double> tiempo_transcurrido);


    virtual void inflingir_danio(Personaje *personaje, std::chrono::duration<double> tiempo_transcurrido);

    //Metodo para testing;

    virtual void matar();

    virtual void revivir();

    
    // Acciones

    // Getters Snapshot
    virtual uint32_t obtener_posicionX();

    virtual uint32_t obtener_posicionY();

    virtual uint8_t obtener_vida();

    virtual uint8_t obtener_movimiento();

    virtual uint32_t obtener_ancho();

    virtual uint32_t obtener_alto();

    virtual int obtener_danio();

    virtual bool mirando_izquierda();

    virtual uint32_t obtener_puntos();
    
    virtual uint8_t obtener_atacando(){
        return esta_atacando;
    }

    virtual uint8_t obtener_item() = 0;

    // Getters Snapshot

    virtual void actualizar_posicion(std::chrono::duration<double> tiempo_transcurrido, std::map<uint32_t, Objeto*>& map_objetos_solidos);

    virtual ~Enemigo();

    // Metodos virtuales para los diferentes personajes enemigos

    virtual uint8_t obtener_personaje() = 0;
};

#endif
