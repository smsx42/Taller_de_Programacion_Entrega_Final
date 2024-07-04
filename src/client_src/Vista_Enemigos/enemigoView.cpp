#include "enemigoView.h"

EnemigoView::EnemigoView() : posicion_x(0), posicion_y(0), width(50), height(50), 
facingLeft(false), isMoving(false), estaVivo(true), contador_desapariciones(0), factory(this->animaciones) {
    this->sonido = std::make_unique<SDL2pp::Chunk>(PATH_SONIDO_ENEMIGO_DESAPARECER);
}

void EnemigoView::actualizar_vista_enemigo(EventoEnemigo &evento, float df) {

    this->posicion_x = evento.posicion_x;
    this->posicion_y = evento.posicion_y;

    this->facingLeft = evento.mirando_izquierda;
    this->estaVivo = evento.esta_vivo;

    this->isMoving = true;
    if(this->isMoving && this->estaVivo) {
        this->animaciones.at(CAMINANDO)->acualizar(df);
        contador_desapariciones = 0;
    } else if(!this->estaVivo) {
        this->animaciones.at(DESAPARECER)->en_loop(false);
        this->animaciones.at(DESAPARECER)->acualizar(0.4 * df);
    }

    if(this->estaVivo){
        this->animaciones.at(DESAPARECER)->reset_frame();
    }
}

void EnemigoView::renderizar_enemigo(std::unique_ptr<SDL2pp::Renderer> &render, int cam_x, int cam_y) {

    SDL2pp::Rect enemigo(posicion_x-cam_x, posicion_y-cam_y, width, height);

    if(this->estaVivo) {
        SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        animaciones.at(CAMINANDO)->animar(*render, enemigo, flip);
    } else if(!this->estaVivo) {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        animaciones.at(DESAPARECER)->animar(*render, enemigo, flip);
    }
}

void EnemigoView::crear_sonido(SDL2pp::Mixer &reproductor_audio) {
    
    if(!this->estaVivo && this->contador_desapariciones == 0){
        this->sonido->SetVolume(30);
        reproductor_audio.PlayChannel(-1, *sonido);
        contador_desapariciones ++;
    }
    
}

EnemigoView::~EnemigoView() {}
