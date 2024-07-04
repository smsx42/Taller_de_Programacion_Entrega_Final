#include "personajeView.h"
#include <iostream>

#define WIDTH 2000
#define HEIGHT 2000
#define PERSONAJE_HEIGHT 50
#define PERSONAJE_WIDTH 50



PersonajeView::PersonajeView(EventoPersonaje &evento) : id_jugador(evento.id_jugador), posicion_x(evento.posicion_x), posicion_y(evento.posicion_y), width(PERSONAJE_WIDTH), height(PERSONAJE_HEIGHT), 
facingLeft(false), isMoving(false), isRunning(false), isJumping(false), isShooting(false), stopShooting(false),
vida(0), puntaje(0), contador_golpes(0), contador_saltos(0) {
    this->sonidos.insert(std::make_pair(SALTANDO, std::make_unique<SDL2pp::Chunk>(PATH_SONIDO_SALTO)));
}

bool PersonajeView::obtener_face() {
    return facingLeft;
}

void PersonajeView::actualizar_vista_personaje(EventoPersonaje const &evento, float dt) {
    
    this->isMoving = bool (!evento.esta_quieto);
    this->isRunning = bool (evento.esta_corriendo);
    this->isJumping = bool (evento.esta_saltando);
    this->isShooting = bool (evento.esta_disparando);
    this->isIntoxicated = bool (evento.esta_intoxicado);
    this->estado = evento.codigo_estado;
    this->posicion_x = evento.posicion_x;
    this->posicion_y = evento.posicion_y;
    this->saltoHorizontal = evento.salto_horizontal;

    facingLeft = evento.mirando_izquierda;

    if(estado == ESTADO_SALTANDO) {
        if (this->isShooting) {
            this->animaciones.at(DISPARO_SALTANDO)->en_loop(true);
            this->animaciones.at(DISPARO_SALTANDO)->acualizar(dt);
        } else{
            if(saltoHorizontal){
                this->animaciones.at(SALTANDO_HORIZONTAL)->en_loop(false);
                this->animaciones.at(SALTANDO_HORIZONTAL)->acualizar(dt*1.5);
            }else{
                this->animaciones.at(SALTANDO)->en_loop(false);
                this->animaciones.at(SALTANDO)->acualizar(dt);
            }
        }
    }  else if(estado == ESTADO_CAMINANDO) {
        if (this->isIntoxicated) {
            this->animaciones.at(INTOXICADO_CAMINANDO)->en_loop(true);
            this->animaciones.at(INTOXICADO_CAMINANDO)->acualizar(dt);
        } else{
            this->animaciones.at(CAMINANDO)->en_loop(true);
            this->animaciones.at(CAMINANDO)->acualizar(dt);
        }
    } else if (estado == ESTADO_CORRIENDO){
        this->animaciones.at(CORRIENDO)->en_loop(true);
        this->animaciones.at(CORRIENDO)->acualizar(dt);
    } else if(estado == ESTADO_QUIETO) {
        if (this->isShooting) {
            this->animaciones.at(DISPARO_QUIETO)->en_loop(true);
            this->animaciones.at(DISPARO_QUIETO)->acualizar(dt);
        } else if(this->isIntoxicated){
            this->animaciones.at(INTOXICADO_QUIETO)->en_loop(true);
            this->animaciones.at(INTOXICADO_QUIETO)->acualizar(dt);
        } else {
            this->animaciones.at(QUIETO_CLIENTE)->en_loop(true);
            this->animaciones.at(QUIETO_CLIENTE)->acualizar(0.5*dt);
        }
    } else if( estado == ESTADO_HERIDO){
        this->animaciones.at(HERIDO)->en_loop(false);
        this->animaciones.at(HERIDO)->acualizar(dt*0.4);
    } else if( estado == ESTADO_MUERTO){
        this->animaciones.at(MUERTO)->en_loop(false);
        this->animaciones.at(MUERTO)->acualizar(dt*0.4);
    } else if ( estado == ESTADO_ESPECIAL){
        this->animaciones.at(HABILIDAD)->en_loop(false);
        this->animaciones.at(HABILIDAD)->acualizar(dt*0.8);
    } else if ( estado == ESTADO_CAYENDO){
        if(saltoHorizontal){
            this->animaciones.at(CAYENDO_HORIZONTAL)->en_loop(true);
            this->animaciones.at(CAYENDO_HORIZONTAL)->acualizar(dt);
        }else{
            this->animaciones.at(CAYENDO)->en_loop(true);
            this->animaciones.at(CAYENDO)->acualizar(dt);
        }
    } else if( estado == ESTADO_TAMBALEAR && !isShooting){
        this->animaciones.at(TAMBALEAR)->en_loop(true);
        this->animaciones.at(TAMBALEAR)->acualizar(dt*0.4);
    }

    // Resetear las animaciones necesarias (No loop)
    if(estado != ESTADO_SALTANDO){
        this->animaciones.at(SALTANDO)->reset_frame();
        this->animaciones.at(SALTANDO_HORIZONTAL)->reset_frame();
    }

    if(estado != ESTADO_ESPECIAL){
        this->animaciones.at(HABILIDAD)->reset_frame();
    }

    if(estado != ESTADO_HERIDO){
        this->animaciones.at(HERIDO)->reset_frame();
    }

    if(estado != ESTADO_MUERTO){
        this->animaciones.at(MUERTO)->reset_frame();
    }


}

void PersonajeView::renderizar_personaje(std::unique_ptr<SDL2pp::Renderer> &render, int cam_x, int cam_y, std::unique_ptr<SDL2pp::Mixer> &reproductor_audio) {
    
    SDL2pp::Rect personaje(posicion_x-cam_x, posicion_y-cam_y, width, height);
    
    // Aca un ejemplo del switch con el patron de estados
    switch (this->estado) {
    case ESTADO_QUIETO:{  
        this->contador_saltos = 0;
        SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        if(isShooting){
            animaciones.at(DISPARO_QUIETO)->animar(*render, personaje, flip);
        }else if(isIntoxicated){
            animaciones.at(INTOXICADO_QUIETO)->animar(*render, personaje, flip);
        }else{
            animaciones.at(QUIETO_CLIENTE)->animar(*render, personaje, flip);
        }
        break;
    }
    case ESTADO_CAMINANDO:{
        this->contador_golpes = 0;
        this->contador_saltos = 0;
        SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        if(isIntoxicated){
            animaciones.at(INTOXICADO_CAMINANDO)->animar(*render, personaje, flip);
        }else{
            animaciones.at(CAMINANDO)->animar(*render, personaje, flip);
        }
        break;
    }
    case ESTADO_CORRIENDO:{
        SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        animaciones.at(CORRIENDO)->animar(*render, personaje, flip);
        break;
    }
    case ESTADO_SALTANDO:{
        SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        if(isShooting){
            animaciones.at(DISPARO_SALTANDO)->animar(*render, personaje, flip);
        }else{
            if(saltoHorizontal){
                animaciones.at(SALTANDO_HORIZONTAL)->animar(*render, personaje, flip);
            }else{
                animaciones.at(SALTANDO)->animar(*render, personaje, flip);
            }
        }
        break;
    }
    case ESTADO_HERIDO:{
        SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        animaciones.at(HERIDO)->animar(*render, personaje, flip);
        break;
    }
    case ESTADO_MUERTO:{
        SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        animaciones.at(MUERTO)->animar(*render, personaje, flip);
        break;
    }
    case ESTADO_ESPECIAL:{
        SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        animaciones.at(HABILIDAD)->animar(*render, personaje, flip);
        break;
    }
    case ESTADO_CAYENDO:{
        SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        if(isShooting){
            animaciones.at(DISPARO_SALTANDO)->animar(*render, personaje, flip);
        }else{
            if(saltoHorizontal){
                animaciones.at(CAYENDO_HORIZONTAL)->animar(*render, personaje, flip);
            }else{
                animaciones.at(CAYENDO)->animar(*render, personaje, flip);
            }
        }
        break;
    }
    case ESTADO_TAMBALEAR:{
        SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        animaciones.at(TAMBALEAR)->animar(*render, personaje, flip);
        break;
    }
    default:
        break;
    }
    
    
}

void PersonajeView::crear_sonido(SDL2pp::Mixer &reproductor_audio) {

    if(estado == ESTADO_SALTANDO && contador_saltos == 0) {
        reproductor_audio.PlayChannel(-1, *this->sonidos.at(SALTANDO));
        contador_saltos ++;
    } else if(estado == ESTADO_HERIDO && contador_golpes == 0) {
        reproductor_audio.PlayChannel(-1, *this->sonidos.at(GOLPE));
        contador_golpes ++;
    }

}

PersonajeView::~PersonajeView() {}