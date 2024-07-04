#ifndef SERVER_PERSONAJE_H_
#define SERVER_PERSONAJE_H_

#include <chrono>
#include <cmath>
#include <iostream>
#include <map>
#include "../common_src/accion.h"
#include "../common_src/evento.h"
#include "../common_src/codigo_estado.h"
#include "../enemigo/enemigo.h"
#include "../estado/estado.h"
#include "../objeto/objeto.h"
#include "../rectangulo.h"
#include "../triangulo.h"
#include "../configuracion.h"


#include "../bala/bala.h"





class Objeto;
class Estado;

class Personaje {
protected:
    uint32_t id_jugador;
    uint32_t posicion_x;
    uint32_t posicion_y;
    int vida; //DEBE SER INT PARA PODER SER NEGATIVO
    bool esta_quieto;
    uint32_t ancho;
    uint32_t alto;

    int velocidad_x;
    int velocidad_y;


    bool corriendo;

    bool saltando;
    bool salto_horizontal;
    bool en_diagonal;
    bool inclinar;
    uint8_t rotacion;
    double tiempo_salto;

    bool usando_especial;
    double tiempo_especial;

    uint8_t direccion_mirando;


    bool esta_disparando;
    bool muerto;

    bool invulnerable;
    double tiempo_invulnerable;

    bool intoxicado;
    double tiempo_intoxicado;

    Estado *estado;

    bool en_superficie;

    uint32_t puntos;

    uint8_t bala_actual;
    double tiempo_disparo;
    std::map<uint8_t,int> municiones;
    std::map<uint8_t,double> tiempos_recarga; 

    uint8_t danio_habilidad;

    std::vector<SpawnPoint> spawns;

public:
    explicit Personaje(uint32_t id_jugador, std::vector<SpawnPoint> spawns);


    int obtener_velocidad(){
        return velocidad_x;
    }

    int obtener_velocidad_y(){
        return velocidad_y;
    }
    // Acciones

    virtual void mover_derecha(std::chrono::duration<double> tiempo_transcurrido);

    virtual void mover_izquierda(std::chrono::duration<double> tiempo_transcurrido);

    virtual void mover_arriba(std::chrono::duration<double> tiempo_transcurrido);

    virtual void mover_abajo();

    virtual void quedarse_quieto();

    virtual void correr_rapido(std::chrono::duration<double> tiempo_transcurrido);

    virtual void correr();

    virtual void recibir_golpe(Bala bala, std::chrono::duration<double> tiempo_transcurrido);

    virtual void recibir_golpe(Enemigo *enemigo, std::chrono::duration<double> tiempo_transcurrido);

    virtual void recibir_golpe(uint8_t golpe, std::chrono::duration<double> tiempo_transcurrido);

    virtual void inflingir_danio_bala(Enemigo *enemigo, std::chrono::duration<double> tiempo_transcurrido);

    virtual void inflingir_danio_bala(Personaje *personaje, std::chrono::duration<double> tiempo_transcurrido);

    virtual void inflingir_danio_habilidad(Enemigo *enemigo, std::chrono::duration<double> tiempo_transcurrido);

    virtual void inflingir_danio_habilidad(Personaje *personaje, std::chrono::duration<double> tiempo_transcurrido);

    virtual uint8_t disparar(std::chrono::duration<double> tiempo_transcurrido);

    virtual void dejar_disparar();

    virtual bool hay_colision(uint32_t pos_x, uint32_t pos_y, uint32_t ancho, uint32_t largo);

    virtual bool mirando_izquierda();

    virtual void posicion_X(uint32_t x);

    virtual void posicion_Y(uint32_t y);

    virtual void revivir();

    virtual void volverse_invulnerable(double tiempo);

    virtual void volverse_vulnerable();

    virtual void intoxicarse(double tiempo);

    virtual void asignar_puntos(uint32_t puntos);

    virtual void curarse(int vida_restaurada);

    virtual void cambiar_bala_siguiente();

    virtual void agarrar_municion(uint8_t codigo_municion, int municion);

    virtual uint8_t obtener_puntos_muerte();

    // Acciones

    // Getters Snapshot
    virtual uint32_t obtener_posicionX();

    virtual uint32_t obtener_posicionY();

    virtual uint8_t obtener_vida();

    virtual uint8_t obtener_movimiento();

    virtual uint8_t obtener_corriendo();

    virtual uint8_t obtener_habilidad();

    virtual uint8_t obtener_saltando();

    virtual uint8_t obtener_disparando();

    virtual uint8_t obtener_estado();

    virtual bool esta_muerto();

    virtual bool es_invulnerable();

    virtual uint32_t obtener_ancho();

    virtual uint32_t obtener_alto();

    virtual uint8_t obtener_intoxicado();

    virtual uint32_t obtener_puntos();

    virtual uint8_t obtener_bala_actual();

    virtual uint32_t obtener_municion_actual();

    virtual uint8_t obtener_danio_habilidad();
    
    virtual uint8_t obtener_salto_horizontal();

    virtual uint8_t obtener_rotacion();

    virtual uint8_t obtener_diagonal();

    // Getters Snapshot

    virtual void actualizar_posicion(std::chrono::duration<double> tiempo_transcurrido,
                                     std::map<uint32_t, Objeto*>& map_objetos, std::map<uint32_t, std::unique_ptr<Objeto>>& map_objetos_comunes);

    virtual ~Personaje();

    // Metodos virtuales para los diferentes personajes

    virtual uint8_t obtener_personaje() = 0;

    virtual void usar_habilidad(std::chrono::duration<double> tiempo_transcurrido) = 0;


public:
    // Logica de Estados
    void cambiarEstado(Estado *estado);

    void manejarEstado(uint8_t codigo_estado, std::chrono::duration<double> tiempo_transcurrido);

    void actualizar(double tiempo);
};

#endif
