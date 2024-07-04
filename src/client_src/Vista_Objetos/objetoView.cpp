#include "objetoView.h"

ObjetoView::ObjetoView() : posicion_x(0), posicion_y(0), widht(25), height(25),
contador_agarres(0), factory(this->animaciones) {}

void ObjetoView::actualizar_vista_objeto(EventoObjeto &evento, float df) {

    this->posicion_x = evento.posicion_x;
    this->posicion_y = evento.posicion_y;
    this->mostrarse = evento.mostrandose;
    if(this->mostrarse) {
        this->animaciones.at(Mostrar)->acualizar(df);
        contador_agarres = 0;
    } else {
        this->animaciones.at(AGARRAR)->en_loop(false);
        this->animaciones.at(AGARRAR)->acualizar(0.4 *df);
        contador_agarres++;
        mostrarse = false;
    }

    if(this->mostrarse){
        this->animaciones.at(AGARRAR)->reset_frame();
    }
}

void ObjetoView::renderizar_objeto(std::unique_ptr<SDL2pp::Renderer> &render, int cam_x, int cam_y) {

    SDL2pp::Rect objeto(posicion_x-cam_x, posicion_y-cam_y, widht, height);
    
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    
    if(this->mostrarse) {
        this->animaciones.at(Mostrar)->animar(*render, objeto, flip);
    } else {
        this->animaciones.at(AGARRAR)->animar(*render, objeto, flip);
    }
}

void ObjetoView::reproducir_audio_objeto(std::unique_ptr<SDL2pp::Mixer> &reproductor_audio) {
    
    if(contador_agarres == 1) {
        reproductor_audio->PlayChannel(-1, *sonido);
    }
    
}


bool ObjetoView::mostrandose(){
    return mostrarse;
}

ObjetoView::~ObjetoView() {}