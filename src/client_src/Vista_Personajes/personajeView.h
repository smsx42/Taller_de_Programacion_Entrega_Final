#ifndef PERSONAJEVIEW_H_
#define PERSONAJEVIEW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "../src/client_src/Animaciones/animacion.h"
#include "../src/common_src/codigo_estado.h"
#include <memory>
#include "../src/common_src/evento.h"
#include <map>
#include "../src/client_src/direcciones.h"
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Chunk.hh> 

class PersonajeView {

    protected:
    
    uint32_t id_jugador;
    int vida;
    int puntaje;
    int tipo_bala;
    int cantidad_municion;
    int posicion_x;
    int posicion_y;
    int width;
    int height;
    std::map<std::string, std::unique_ptr<Animacion>> animaciones;
    std::map<std::string, std::unique_ptr<SDL2pp::Chunk>> sonidos; 
    bool facingLeft;
    bool isMoving;
    bool isRunning;
    bool isJumping;
    bool isShooting;
    bool stopShooting;
    bool isIntoxicated;
    bool saltoHorizontal;
    int contador_golpes;
    int contador_saltos;
    
    uint8_t estado; // Almacena el estado actual del personaje

    public:

    virtual bool obtener_face();

    PersonajeView(EventoPersonaje &evento);

    virtual ~PersonajeView();

    virtual void actualizar_vista_personaje(EventoPersonaje const &evento,float dt);

    virtual void renderizar_personaje(std::unique_ptr<SDL2pp::Renderer> &render, int cam_x, int cam_y, std::unique_ptr<SDL2pp::Mixer> &reproductor_audio);
    
    virtual void crear_sonido(SDL2pp::Mixer &reproductor_audio);

    virtual void definir_tipo_bala(uint8_t tipo_bala) {
        this->tipo_bala = int(tipo_bala);
    }

    virtual int obtener_tipo_bala() {
        return this->tipo_bala;
    }

    virtual void definir_cantidad_municion(uint32_t municiones) {
        this->cantidad_municion = int(municiones);
    }

    virtual int obtener_cantidad_municion() {
        return this->cantidad_municion;
    }

    virtual void definir_puntos(uint32_t puntos) {
        this->puntaje = int(puntos);
    }

    virtual int obtener_puntos() {
        return this->puntaje;
    }

    virtual uint32_t obtener_id_jugador() {
        return id_jugador;
    }

    virtual void definir_vida(uint8_t vida) {
        this->vida = int(vida);
    }

    virtual int obtener_vida() {
        return this->vida;
    }

    virtual int obtener_posicion_x() {
        return posicion_x;
    }

    virtual int obtener_posicion_y() {
        return posicion_y;
    }

    virtual void definir_posicion_x(int x) {
        posicion_x = x;
    }

    virtual void definir_posicion_y(int y) {
        posicion_y = y;
    }

};

#endif //PERSONAJEVIEW_H_