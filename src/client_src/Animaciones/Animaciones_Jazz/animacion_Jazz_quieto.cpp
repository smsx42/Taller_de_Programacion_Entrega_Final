#include "animacion_Jazz_quieto.h"

Animacion_Jazz_Quieto::Animacion_Jazz_Quieto() : Animacion() {}

void Animacion_Jazz_Quieto::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_JAZZ_QUIETO, render)));
    this->size_frame = 40.0F;
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
}

Animacion_Jazz_Quieto::~Animacion_Jazz_Quieto() {}