#include "animacion_Lori_quieto.h"

Animacion_Lori_Quieto::Animacion_Lori_Quieto() : Animacion() {}

void Animacion_Lori_Quieto::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_LORI_QUIETO, render)));
    this->size_frame = texturas->GetHeight();
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
}

Animacion_Lori_Quieto::~Animacion_Lori_Quieto() {}