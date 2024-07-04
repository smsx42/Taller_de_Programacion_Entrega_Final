#include "balaView.h"
BalaView::BalaView(bool face, int x, int y, uint8_t tipo, SDL2pp::Renderer *render) : 
posicion_x(y), posicion_y(y), width(BALA_WIDTH), height(BALA_HEIGHT), 
facingLeft(face), contador_disparos(0),
animacion_bala(nullptr), factory(this->animacion_bala, this->sonido) {
    
    this->factory.crear_animaciones_sonidos(tipo);
    this->factory.crear_texturas(render);
}

void BalaView::actualizar(EventoBala const &evento,float dt){

    facingLeft = false;
    if(posicion_x > evento.posicion_x) {
        facingLeft = true;
    }

    this->animacion_bala->acualizar(dt);
    this->posicion_x = evento.posicion_x;
    this->posicion_y = evento.posicion_y;
}


 void BalaView::renderizar(SDL2pp::Renderer &render, int cam_x, int cam_y){
    
    SDL2pp::Rect bala(posicion_x -cam_x, posicion_y-cam_y, 15, 15);

    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_NONE: SDL_FLIP_HORIZONTAL;
    animacion_bala->animar(render, bala, flip);
 
}

void BalaView::crear_sonido(SDL2pp::Mixer &reproductor_sonido) {

    if(contador_disparos == 0) {
        reproductor_sonido.PlayChannel(-1, *this->sonido);
        contador_disparos ++;
    }
}

BalaView::~BalaView() {}
